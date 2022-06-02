### PWManager  
  
PWManager is an offline (no cloud storage of data) password manager.  
Its aim is to ease password management by taking care of password  
creation and storage.  
  
### Usage  
  
Before anything, run `setup.sh` script, otherwise you won't be able  
to use this software.  
  
```
Usage: 
    pwman -l       -> Lists all labels
    pwman          -> Same
    pwman -d LABEL -> Deletes the account labeled LABEL. This is final
    pwman -i LABEL -> Asks for all information (except the password) about
                      the account labeled LABEL
    pwman -g LABEL -> Displays the password (on standard output) of the
                      account labeled LABEL
    pwman -c LABEL [-u USERNAME] [-e EMAIL]
                   -> Creates a new account labeled LABEL. If no 
                      value for USERNAME and EMAIL is provided, a default
                      value will be stored
    pwman -h       -> Displays this message
```
  
### Author  
  
Guillermo MORON USON  
guillermo.moron@laposte.net  
@MisutaGui on GitHub  
