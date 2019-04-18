# ------------------------lan_video_conference（局域网视频会议）------------------------

# videoConferencingServer 服务器
# videoConferencingClient 客户端
# 服务器地址
        Liana 192.168.43.174:2333
        Lzy
        Liang
# -------------------------------------当前版本 -------------------------------------

Client的tcp部分，Client部分请求（注册登录）;Server tcp连接;数据库小部分
客户端部分添加了四个signals（登录注册）

# -------------------------------------JSON部分 -------------------------------------
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
        FROM：xxxEMAILIDxxx
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
        RESULT："1"/"-1"无效账户/"-2"密码错误
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
        GROUPS：[
            {GROUPNAME：
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"]，
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
            }],
            [
            {GROUPNAME：
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
            }],
            [
            {GROUPNAME：
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
            }]
            
        }
    }


