 # Spotify Desktop Frontend Challenge
A spotify fronted application for desktop. It's a selection process challenge.  
The application offers features to create and store locally new playlits, search for tracks through spotify webapi, add new tracks to playlists and play the playlists.

## Build instructions
The project for while has only qmake build configuration. So in order to build this application, `git clone` it and open the .pro file using QtCreator. Configure the project when the IDE prompts you the wizzard. After that choose a build task, build and run.  
  
This project build was tested for QtCreator 4.11 and Qt 5.14 using MinGW 5.3 
  
!!! You may have some trouble building it for x64 windows archtecture with the tools I used to build. While working on this project and building it on Windows x64, I had a problems like the follow: 

`qt.network.ssl: QSslSocket: cannot call unresolved function SSLv23_client_method`  
`qt.network.ssl: QSslSocket: cannot call unresolved function SSL_CTX_new`  
`qt.network.ssl: QSslSocket: cannot call unresolved function SSL_library_init`  
`qt.network.ssl: QSslSocket: cannot call unresolved function ERR_get_error`  
`qt.network.ssl: QSslSocket: cannot call unresolved function ERR_get_error`  

In order to fix this, you must copy files `libeay32.dll` and `ssleay32.dll` from `Qt/Tools/MinGW_folder/opt/bin` to `Qt/Tools/MinGW_folder/bin`  

## Features
* Creating and saving custom playlists locally
* Removing local playlists
* Searching for songs in spotify database using keywords
* Adding songs found in search to local playlists
* Removing songs from local playlists
* _Playing local playlists_ *missing*

## Instructions for Use
### Adding a new playlist
To add a new playlist you must type the desired playlist name in text field in the panel titled "Playlists" and click the + button

### Removing a playlist
In the list of playlistis you must click in the button with a trash icon in order to remove the playlist

### Opening a playlist
Click in the desired playlist to open it in the leftmost panel

### Searching for a song
When you have already opened a playlist, type the keywords in the text field besides the search button, and then hit enter key or press search button

### Adding a new song to a playlist
When you have already opened a playlist and performed a song search, click on the song you want to add to the playlist from the songs available in the search result list

### Removing a song from a playlist
When you have already opened a playlist, click in the trash button of the song you want to remove from the playlist
