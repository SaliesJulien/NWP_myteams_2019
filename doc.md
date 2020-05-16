# **my_teams documentation**
***
## **-> /help** :
    <- 201 Functions aviable on the server
    <- 501 Error syntax in parameters or arguments
***
## **-> /login** _["username"]_
    <- 230 Succesfull login
    <- 330 Client already connected
    <- 530 Authentification failed, name length longer than 32 characters
    <- 501 Error syntax in parameters or arguments
***
## **-> /logout**
    <- 221 Service closing control connection.
    <- 501 Error syntax in parameters or arguments
***
## **-> /users**
    <- 202 List of all users existing on the server
    <- 501 Error syntax in parameters or arguments
***
## **-> /user** _["user_id"]_
    <- 203 User infos
    <- 303 User doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /send** _["user_id"] ["message"]_
    <- 204 sucessfully sent message
    <- 303 User doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /messages** _["user_id"]_
    <- 205 Conversation with "username"
    <- 303 User doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /subscribe** _["team_id"]_

    <- 206 You succesfully subscribed to the team
    <- 304 Team doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /subscribed** ?_["team_id"]_
    <- 207 List of teams that you are in
    <- 208 List of all user in this team
    <- 304 Team doesn't exist
    <- 501 Error syntax in parameters or arguments
***
## **-> /unsubscribe** _["team_id"]_
    <- 209 You succesfully left this team
    <- 304 Team doesn't exist
    <- 305 You aren't in this team
    <- 501 Error syntax in parameters or arguments
***
## **-> /use** ?_["team_id"]_ ?_["channel_id"]_ ?_["thread_id"]_
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
# **-> /create**
### When the context is not defined (/use):
## **-> /create** _["team_name"] ["team_desc"]_
    <- 220 You succesfully created the team "team_name"
    <- 510 This team already exist
    <- 501 Error syntax in parameters or arguments
### When team_uuid is defined (/use “team_uuid”):
## **-> /create** _["channel_name"] ["channel_desc"]_
    <- 221 You succesfully created the channel "channel_name"
    <- 511 This channel already exist
    <- 501 Error syntax in parameters or arguments
### When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
## **-> /create** _["thread_name"] ["thread_desc"]_
    <- 221 You succesfully created the thread "thread_name"
    <- 512 This thread already exist
    <- 501 Error syntax in parameters or arguments
### When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
## **-> /create** _["comment_body"]
    <- 221 You succesfully posted a comment in "thread_name"
    <- 532 Post failed, body length longer than 512 characters
    <- 501 Error syntax in parameters or arguments
***