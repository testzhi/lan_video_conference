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
请求账户的会议列表{
    TYPE： #REQUEST_MEETINGS_LIST
    DATA：{
        FROM：xxxIDxxx
        }
    }
请求退出{
    TYPE：#EXIT
    DATA：{
        FROM： xxxEMAILIDxxx
        }
    }
请求发起会议{
    TYPE： #REQUEST_LAUNCH_MEETING
    DATA：{
        FROM：xxxIDxxx
<!--         INITIATOR -->
<!--         ASSISTANT -->
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
<!--请求回复邀请{
    TYPE： #REQUEST_SEND_INVITATION_RESULT
    DATA：{
        FROM：xxxIDxxx
        RESULT:0/1
        MEETINGID:
        CAUSE
        }
    }-->
<!--请求开始会议{
    TYPE： #REQUEST_START_MEETING
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }-->
<!--请求终止会议{
    TYPE： #REQUEST_STOP_MEETING
    DATA：{
        FROM：xxxIDxxx
        MEETINGID:
        }
    }-->
# 由服务端发送 
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
                    { MEETINGID 
<!--                       INITIATOR -->
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
<!--                       CATAGRO -->
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
<!--                       MEETINGSCALE -->
<!--                       PREDICTEDDURATION -->
<!--                       MEETINGSTATE -->
                      REMARK
                    }
                    { MEETINGID  
<!--                       INITIATOR -->
                      ASSISTANT
                      SPEAKER
                      DATE
                      TIME
<!--                       CATAGRO -->
                      SUBJECT
<!--                       MEETINGNAME -->
<!--                       OWNUNIT -->
<!--                       MEETINGSCALE -->
<!--                       PREDICTEDDURATION -->
<!--                       MEETINGSTATE -->
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
        ERROR
        }
    }  
