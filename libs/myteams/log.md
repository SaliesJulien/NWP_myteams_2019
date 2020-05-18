***
### **client_event_loggedin** = 101|user_id|user_name|
***
### **client_event_loggedout** = 102|user_id|user_name|
***
### **client_event_private_message_received** = 103|user_id|message_body|
***
### **client_event_thread_message_received** = 104|team_id|thread_id|user_id|message|
***
### **client_event_team_created** = 105|team_id|team_name|team_description|
***
### **client_event_channel_created** = 106|channel_id|channel_name|channel_description|
***
### **client_event_thread_created** = 107|thread_id|user_id|_thread_timestamp|thread_title|thread_body|
***
### **client_print_users** = 108|user_id|user_name|user_status|
***
### **client_print_teams** = 109|team_id|team_name|team_description|
***
### **client_team_print_channels** = 110|channel_id|channel_name|channel_description|
***
### **client_channel_print_threads** = 111|thread_id|user_id|thread_timestamp|thread_title|thread_body|
***
### **client_thread_print_replies** = 112|thread_id|user_id|reply_timestamp|reply_body|
***
### **client_private_message_print_messages** = 113|sender_id|timestamp|message|   //PAS FAIT
***
### **client_error_unknown_team** = 114|team_id|
***
### **client_error_unknown_channel** = 115|channel_id|
***
### **client_error_unknown_thread** = 116|thread_id|
***
### **client_error_unknown_user** = 117|user_id|
***
### **client_print_user** = 118|user_id|user_name|user_status|
***
### **client_print_team** = 119|team_id|team_name|team_description|
***
### **client_print_channel** = 120|channel_id|channel_name|channel_description|
***
### **client_print_thread** = 121|thread_id|user_id|thread_timestamp|thread_title|thread_body|
***
### **client_print_team_created** = 122|team_id|team_name|team_description|
***
### **client_print_channel_created** = 123|channel_id|channel_name|channel_description|
***
### **client_print_thread_created** = 124|thread_id|user_id|thread_timestamp|thread_title|thread_body|
***
### **client_print_reply_created** = 125|thread_id|user_id|reply_timestamp|reply_body|
***
### **client_print_subscribed** = 126|user_id|team_id
***
### **client_print_unsubscribed** = 127|user_id|team_id|
***
### **client_error_unauthorized** = 128|
***
### **client_error_already_exist** = 129|
***