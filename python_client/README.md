# Python client for the Dbus filedescriptor Example
+ Python client for the Dbus filedescriptor example based on dbus-next library

## Prerequisites
+ Python3 interpreter
+ Install the `requirements.txt`
    - Ideally within a virual environment
        - `$ python3 -m venv dbus_env`
        - `$ source ./dbus_env/bin/activate`
        - `$ pip3 install -r requirements.txt`
+ Adjust the path to the virtual environment within the `./.vscode/launch.json` file
***Now you can run the program***

## Learnings
+ With dbus-next, we need to explicitly allow file descriptors:
    - https://github.com/altdesktop/python-dbus-next/issues/151
+ Be careful with reading and writing since the read and write pointer can be changed on both sides of the exchanged file descriptor and remains over multuple calls!
    - That is the reason why we need to call the `file.seek(0)` function to read always properly from the received file descriptor in our python client!
    - See:
        * https://man7.org/linux/man-pages/man2/lseek.2.html
        * https://stackoverflow.com/questions/16374425/python-read-function-returns-empty-string