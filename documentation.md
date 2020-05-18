# **my_teams documentation**
_documentation that explain how to use commands aviable on this server and the differents replies code_
***
## **-> /help** :
**description : show help**

    <- 201 Functions aviable on the server
    <- 501 Error syntax in parameters or arguments
***
## **-> /login** _["username"]_
**description : set the username used by client**

    <- 230 Succesfull login
    <- 330 Client already connected
    <- 530 Authentification failed, name length longer than 32 characters
    <- 501 Error syntax in parameters or arguments
***
## **-> /logout**
**description : disconnect the client from the server**

    <- 221 Service closing control connection.
    <- 501 Error syntax in parameters or arguments
***
## **-> /users**
**description : get the list of all users that exist on the domain**

    <- 202 List of all users existing on the server
    <- 501 Error syntax in parameters or arguments
***
## **-> /user** _["user_id"]_
**description : get information about a user**

    <- 203 User infos
    <- 303 User doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /send** _["user_id"] ["message"]_
**description : send a message to a user**

    <- 204 sucessfully sent message
    <- 303 User doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /messages** _["user_id"]_
**description : list all messages exchange with an user**

    <- 205 Conversation with "username"
    <- 303 User doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /subscribe** _["team_id"]_
**description : subscribe to the event of a team and its sub directories (enable receptionof all events from a team)**

    <- 206 You succesfully subscribed to the team
    <- 304 Team doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /subscribed** ?_["team_id"]_
**description : list all subscribed teams or list all users subscribed to a team**

    <- 207 List of teams that you are in
    <- 208 List of all user in this team
    <- 304 Team doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /unsubscribe** _["team_id"]_
**description : unsubscribe from a team**

    <- 209 You succesfully left this team
    <- 304 Team doesn't exist
    <- 305 You aren't in this team
    <- 501 Error syntax in parameters or arguments
***
## **-> /use** ?_["team_id"]_ ?_["channel_id"]_ ?_["thread_id"]_
**description : use specify a context team/channel/thread**

    <- 210 You are now in the team "team_name"
    <- 211 You are now in the channel "channel_name"
    <- 212 You are now in the thread "thread_name"
    <- 213 You are now in the server home
    <- 304 Team doesn't exist
    <- 305 Channel doesn't exist
    <- 306 Thread doesn't exist
    <- 542 You can't go deeper than the server home
    <- 501 Error syntax in parameters or arguments
***
# **-> /CREATE**
### When the context is not defined (/use):
## **-> /create** _["team_name"] ["team_desc"]_
**description : create a new team**

    <- 220 You succesfully created the team "team_name"
    <- 510 This team already exist
    <- 501 Error syntax in parameters or arguments
### When team_uuid is defined (/use “team_uuid”):
## **-> /create** _["channel_name"] ["channel_desc"]_
**description : create a new channel**

    <- 221 You succesfully created the channel "channel_name"
    <- 511 This channel already exist
    <- 501 Error syntax in parameters or arguments
### When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
## **-> /create** _["thread_name"] ["thread_desc"]_
**description : create a new thread**

    <- 222 You succesfully created the thread "thread_name"
    <- 512 This thread already exist
    <- 501 Error syntax in parameters or arguments
### When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
## **-> /create** _["comment_body"]
**description : post a comment in a thread**

    <- 223 You succesfully posted a comment in "thread_name"
    <- 532 Post failed, body length longer than 512 characters
    <- 501 Error syntax in parameters or arguments
***
# **-> /LIST**
### When the context is not defined (/use):
## **-> /list**
**description : list all existing teams**

    <- 231 list of teams that exist on the server
    <- 501 Error syntax in parameters or arguments
### When team_uuid is defined (/use “team_uuid”):
## **-> /list**
**description : list all existing channels**

    <- 232 list of channels that exist on this team
    <- 501 Error syntax in parameters or arguments
### When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
## **-> /list**
**description : list all existing thread**

    <- 233 List of threads that exist on this channel
    <- 501 Error syntax in parameters or arguments
### When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
## **-> /list**
**description : list all comment in a thread**

    <- 234 List of comment that are posted on this thread
    <- 501 Error syntax in parameters or arguments
***
# **-> /INFO**
### When the context is not defined (/use):
## **-> /info**
**description : display currently logged user infos**

    <- 241 Users currently logged
    <- 501 Error syntax in parameters or arguments
### When team_uuid is defined (/use “team_uuid”):
## **-> /info**
**description : display currently selected team infos**

    <- 242 Team "team_name" info
    <- 501 Error syntax in parameters or arguments
### When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
## **-> /info**
**description : display currently selected channel infos**

    <- 243 Channel "channel_name" info
    <- 501 Error syntax in parameters or arguments
### When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
## **-> /info**
**description : display currently selected thread infos**

    <- 244 thread "thread_title" info
    <- 501 Error syntax in parameters or arguments
***
Made by :
+ Julien Salies
+ Lucas Simao
+ Hugo Caulfield