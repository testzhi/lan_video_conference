# ------------------------lan_video_conference（局域网视频会议）
# videoConferencingServer 服务器
# videoConferencingClient 客户端
# 服务器地址
        Liana 192.168.43.174:2333
        Lzy   192.168.43.7:2333
        Liang
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
    
<!--     若需要在终端查看数据库 mysql -u VideoConferencingServer  -->
    
    
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
    ATTENDSTATE         -1缺席0迟到1正常参加
    REMARK              缺席原因/迟到时长
表7  NotificationsTable
    CATAGRO             1助手发起的会议邀请
    STATE               0暂未处理          1已经处理通知（同意）     2已经处理通知（拒绝）      <!---1已经超时失效-->
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

# -------------------------------------JSON部分
# 由客户端发送     #
请求注册{
    TYPE：#REGISTER,
    DATA：{
        REALNAME  ： 
        PASSWD    :  xxxxxxx
        EMAIL     :  liannaxu07@gmail.com
        AVATAR    ：
        COMPANY   ：
        DEPARTMENT：
        GROUP     ：
        PHONE     ：
        }
    }
请求登录{   Note:登录可用ID或Email，退出凭借ID
    TYPE: #LOGIN
    DATA：{
        EMAILID:
        PASSWD:
        }
    }
请求退出{   Note:登录可用ID或Email，退出凭借ID
    TYPE：#EXIT
    DATA：{
        FROM： xxxEMAILIDxxx
        }
    }
请求账户细节信息{
    TYPE： #REQUEST_ACCOUNT_DETAIL
        DATA：{
            FROM：xxxEMAILIDxxx
            }
    }
请求账户的同事列表{
    TYPE： #REQUEST_COLLEAGUE_LIST
    DATA：{
        FROM：xxxIDxxx
        }
    }
请求账户的会议邀请列表{
    TYPE： #REQUEST_MEETING_INVITATIONS_LIST
    DATA：{
        FROM：xxxIDxxx
        }
    }
<!--请求账户的会议提醒列表{
    TYPE： #REQUEST_MEETING_REMINDERS_LIST
    DATA：{
        FROM：xxxIDxxx
        }
    }-->
请求账户的会议列表{
    TYPE： #REQUEST_MEETINGS_LIST
    DATA：{
        FROM：xxxIDxxx
        }
    }
请求发起会议{
    TYPE： #REQUEST_LAUNCH_MEETING
    DATA：{
        FROM：xxxIDxxx
<!--         INITIATOR -->
        ASSISTANT
        SPEAKER
        DATE
        TIME
        CATEGORY
        SUBJECT
<!--         MEETINGNAME -->
<!--         OWNUNIT -->
        MEETINGSCALE
        PREDICTEDDURATION
        REMARK
        ATTENDEES:[{EMAILID:    userid更好},
                   {EMAILID:    }
                   {EMAILID:    }
                  ]
        }
    }
请求开始会议{
    TYPE： #REQUEST_START_MEETING
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }
请求终止会议{
    TYPE： #REQUEST_STOP_MEETING
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }
<!--请求延迟会议{
    TYPE： #REQUEST_DELAY_MEETING
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }-->
<!--请求取消会议{
    TYPE： #REQUEST_CANCEL_MEETING
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }-->
<!--请求修改会议相关信息{
    TYPE： #REQUEST_CHANGE_MEETING_INFO
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }-->
请求回复邀请{
    TYPE： #REQUEST_SEND_INVITATION_RESULT
    DATA：{
        FROM：xxxIDxxx
        RESULT:0/1
        MEETINGID:
        CAUSE
        }
    }
# 由服务端发送     _
注册结果{
    TYPE：_REGISTER
    DATA：{
        RESULT："1"成功/"-1"email已注册
        USERID：
        EMAIL:
        ERROR:
    }
登录成功与否{
    TYPE：_LOGIN
    DATA：{
        EMAILID:
        RESULT："1"/"-1"无效账户/"-2"密码错误/"-3"重复登录
        ERROR:
        }
    }
账户初始化信息{
    TYPE：_INITIALIZE_ACCOUNT_DETAIL
        DATA：{
            USERID    ：
            EMAIL     :  liannaxu07@gmail.com
            REALNAME  ： 
            AVATAR    ：
            COMPANY   ：
            DEPARTMENT：
            GROUP     ：
            PHONE     ：
            }
    }
账户的同事列表{
    TYPE：_INITIALIZE_COLLEAGUE_LIST
    DATA:{
        DEPARTMENTS：[
                    { DEPARTMENTNAME：
                      GROUPS:[
                                {   GROUPNAME:
                                    EMPLOYEES:[     {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:}
                                              ]
                                }
                                {   GROUPNAME:
                                    EMPLOYEES:[     {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:}
                                              ]
                                }
                             ]
                    }
                    { DEPARTMENTNAME：
                      GROUPS:[
                                {   GROUPNAME:
                                    EMPLOYEES:[     {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:}
                                              ]
                                }
                                {   GROUPNAME:
                                    EMPLOYEES:[     {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:}
                                              ]
                                }
                                {   GROUPNAME:
                                    EMPLOYEES:[     {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:},
                                                    {REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:}
                                              ]
                                }
                             ]
                    }
                    ]
        }
                    
              

账户的会议邀请列表{
    TYPE：_INITIALIZE_MEETING_INVITATIONS_LIST
    DATA:{
        INVITATIONS：[
                    { INITIATOR
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
<!--                       CATAGRO -->
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
                      MEETINGSCALE
                      PREDICTEDDURATION
                      MEETINGSTATE
                      REMARK
                    }
                    { INITIATOR
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
<!--                       CATAGRO -->
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
                      MEETINGSCALE
                      PREDICTEDDURATION
                      MEETINGSTATE
                      REMARK
                    }
                    ]
        }
                    
账户的会议提醒列表{
    TYPE：_INITIALIZE_MEETING_REMINDERS_LIST
    DATA:{
        REMINDERS：[
                    { INITIATOR
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
<!--                       CATAGRO -->
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
                      MEETINGSCALE
                      PREDICTEDDURATION
                      MEETINGSTATE
                      REMARK
                    }
                    { INITIATOR
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
<!--                       CATAGRO -->
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
                      MEETINGSCALE
                      PREDICTEDDURATION
                      MEETINGSTATE
                      REMARK
                    }
                    ]
        }
账户的会议列表{
    TYPE： _INITIALIZE_MEETINGS_LIST
    DATA：{
        MEETINGS：[
                    { 
<!--                       INITIATOR -->
                      MEETINGID
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
                      CATEGORY
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
                      MEETINGSCALE
                      PREDICTEDDURATION
                      MEETINGSTATE
                      REMARK
                    }
                    { 
<!--                       INITIATOR -->
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
                      CATEGORY
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
                      MEETINGSCALE
                      PREDICTEDDURATION
                      MEETINGSTATE
                      REMARK
                    }
                    ]
    }
发起会议结果{
    TYPE： _LAUNCH_MEETING_RESULT
    DATA：{
        MEETINGID
        RESULT：0/1
        }
    }          
