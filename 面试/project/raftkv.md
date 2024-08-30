## Raft::AppendEntries1

1. 检查term是否小于自己的term
   * 小于：设置reply错误信息；然后返回。
   * 大于：设置自身term为接受到的term，设置自身状态为跟随者。