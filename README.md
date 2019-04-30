# ------------------------lan_video_conference（局域网视频会议）
# videoConferencingServer 服务器
# videoConferencingClient 客户端
# 服务器地址
        Liana 192.168.43.174:2333
        Lzy   192.168.43.7:2333
        Liang 192.168.43.:2333
# -------------------------------------当前版本

Client的tcp部分，Client部分请求（注册登录）;  Server tcp连接;   数据库部分;      Server部分反馈（注册登录）
客户端部分添加了四个signals（登录注册）
# ------------------------------------数据库部分 
第一次配置
    mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
    systemctl start mysqld
    mysql_secure_installation 
    systemctl restart mysqld
    
    将mariadb connector解压缩，将include文件夹下内容复制到/usr/include或/usr/local/include
                             将lib文件夹下内容复制到/usr/lib或/usr/local/lib
                             将bin文件夹下内容复制到/usr/bin或/usr/local/bin
    source /sbin/ldconfig
    mysql -u root -p 密码
    create user 'VideoConferencingServer'@'localhost';
    create database VideoConferencingDB;
    grant all on VideoConferencingDB.* to 'VideoConferencingServer'@'localhost';
    
n次以后
    systemctl start mysqld
    

<!--
    mysql -u VideoConferencingServer 
    drop database VideoConferencingDB; create database VideoConferencingDB;
    use VideoConferencingDB;
select * from EmployeesTable;
select * from MeetingsTable;
select * from AttendeesTable;
select * from NotificationsTable;
-->
    
[Note:如果想避免重复输入以上语句，可以直接输入（即开机自启数据库）                     ]
[    systemctl enable mysqld@.service  或者 systemctl enable mysqld           ]
[    若要关闭上述语句                                                           ]
[    systemctl disable mysqld@.service 或者 systemctl disable mysqld@.service ]




数据库VideoConferencingServer
表1  EmployeesTable
    STATE       -1禁用/0不在线/1在线
表2  CompaniesTable
表3  DepartmentsTable
表4  GroupsTable
表5  MeetingsTable
    INITIATOR           会议提议人（）
    ASSISTANT           会议助手
    SPEAKER             主讲人
    CATAGRO             0分享型1讨论型
    OWNUNIT             所属单位/部门/组（）
    MEETINGSCALE        人数
    PREDICTEDDURATION   预测时长（）min
    REMARK              会议备注
    MEETINGSTATE        0未开始1进行中2完成
表6  AttendeesTable
    ATTENDSTATE         -1缺席1同意参加(暂时未考虑0迟到) 2参加中  3早退4结束
    REMARK              缺席原因/迟到时长
表7  NotificationsTable
    CATAGRO             1assistant/speaker发起的会议邀请
    STATE               0暂未处理          1已经处理通知（同意）     -1已经超时失效/已经处理通知（拒绝）
    SUBJECT是指其他出去会议通知类型的主题，而会议通知的主题即会议主题
    
表2
表2
# ------------------------------------libjrtp部分
[若删除已经cmake安装的软件     cat install_manifest.txt|while read f; do sudo rm "$f"; done]
jthread解压缩
    cmake .
    make
    make install
jrtp解压缩
    camke .
    make
    make instal
    ln -s /usr/local/lib64/libjthread.so.1.3.3  /usr/lib   或者   ln -s /usr/local/lib/libjthread.so.1.3.3  /usr/lib
    ln -s /usr/local/lib64/libjrtp.so.3.11.1 /usr/lib      或者 ln -s /usr/local/lib/libjrtp.so.3.11.1 /usr/lib



