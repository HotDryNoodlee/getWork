## Raft::AppendEntries1

1. 检查term是否小于自己的term
   * 小于：设置reply错误信息；然后返回。
   * 大于：设置自身term为接受到的term，设置自身状态为跟随者。


## 复制状态机 （目的）

* 复制状态机(Replicated state machine)的概念：
  * 相同的初始状态+相同的输入=相同的结束状态
  * 多个节点上，从相同的初始状态开始，执行相同的一串命令，产生相同的最终状态。	
  * 在Raft中，leader将客户端请求(command)封装到一个个log entry中，将这些log entries复制到所有follower节点，然后大家按相同顺序应用logentries中的command，根据复制状态机的理论，大家的结束状态肯定是一致的。


## 领导者选举


* Raft内部有一种心跳机制，如果存在leader，那么它就会周期性地向所有follower发送心跳，来维持自己的地位。如果follower一段时间没有收到心跳，那么他就会认为系统中没有可用的leader了，然后开始进行选举。	

* 开始一个选举过程后，follower先增加自己的当前任期号，并转换到candidate状态。然后投票给自己，并且并行地向集群中的其他服务器节点发送投票请求(RequestVote RPC)。

* 每个节点会有一个随机的选举超时时间。

   ~~~c++
   message RequestVoteArgs  {
      int32 Term         =1;
      int32 CandidateId  =2;
      int32 LastLogIndex =3;
      int32 LastLogTerm  =4;
   }

   message RequestVoteReply  {
      int32 Term        =1;
      bool VoteGranted  =2;
   }
   ~~~


## 日志复制

* Leader并行发送AppendEntries RPC给follower，让它们复制该条目。当该条目被超过半数的follower复制后，leader就可以在本地执行该指令并把结果返回客户端。

* 我们把本地执行指令，也就是leader应用日志与状态机这一步，称作提交。

* 意外情况：
  * 1&2. follower缓慢、follower宕机
      * 如果有follower因为某些原因没有给leader响应，那么leader会不断地重发追加条目请求(AppendEntries RPC)，哪怕leader已经回复了客户端。
      * 如果有follower崩溃后恢复，这时Raft追加条目的一致性检查生效，保证follower能按顺序恢复崩溃后的缺失的日志。
      * Raft的一致性检查:leader在每一个发往follower的追加条目RPC中，会放入前一个日志条目的索引位置和任期号，如果follower在它的日志中找不到前一个日志，那么它就会拒绝此日志，leader收到follower的拒绝后，会发送前一个日志条目，从而逐渐向前定位到follower第一个缺失的日志。

  * leader宕机
      * 如果leader崩溃，那么崩溃的leader可能已经复制了日志到部分follower但还没有提交而被选出的新leader又可能不具备这些日志，这样就有部分follower中的日志和新leader的日志不相同。
      * Raft在这种情况下，leader通过强制follower复制它的日志来解决不一致的问题，这意味着follower中跟leader冲突的日志条目会被新 leader的日志条目覆盖(因为没有提交，所以不违背外部一致性)。


   ~~~c++
   message AppendEntriesArgs  {
      int32 Term        =1;
      int32 LeaderId       =2;
      int32 PrevLogIndex =3;
      int32 PrevLogTerm  =4;
      repeated LogEntry Entries  = 5;
      int32 LeaderCommit  = 6;
   }
   message AppendEntriesReply {
      int32 Term =1; 
      bool Success =2;
   }
   ~~~


## 安全性

1. leader宕机处理：选举限制

   *  该限制确保任何给定任期的leader包含在先前任期中提交的所有条目
   *  如果投票者自己的日志比候选人的日志更最新，那么他就拒绝投票。Raft通过比较日志中最后一个条目的索引和项来确定两个日志中哪个更为最新。如果日志的最后一个条目具有不同的任期，则具有较大的任期的日志更为最新。如果日志以相同的任期结尾，则以较长的日志为准。


2. leader宕机处理：新leader是否提交之前任期的日志条目。

   * 只有来自领导者当前任期的日志条目通过计算副本数量来提交；一旦以这种方式提交了来自当前任期的条目，那么由于日志匹配属性，所有先前的条目都将间接提交。

3. follower和candidate宕机

   * 如果follower或candidate崩溃了，那么后续发送给他们的RequestVote和AppendEntries RPCs都会失败。
   * Raft通过无限的重试来处理这种失败。如果崩溃的机器重启了，那么这些RPC就会成功地完成。
   * 如果一个服务器在完成了一个RPC，但是还没有相应的时候崩溃了，那么它重启之后就会再次收到同样的请求。(Raft的RPC都是幂等的)

4. 时间与可用性限制
   * 广播时间(broadcastTime)<<选举超时时间(electionTimeout)<<平均故障时间(MTBF)


## 集群成员变更
   
   * 两阶段法防止脑裂

1. 补充规则


单节点变更
