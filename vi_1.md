# vi editor

## About vi ( file editing work )
- vi(pronounced "vee-eye")
    - A screen-oriented text editor
    - The standard Unix editor
    - It is short for "visual"
    - There are lots of clones(vim, nvi, elvis, macvim)

## vi Modes
- Command Mode ( default mode )
    - Command mode is the mode you are in when you start
    - Move cursor, Move page, Delete, Copy, Paste,,,
- Insert(or Text) Mode ( Edit )
    - The mode in which text is created
    - Literally typed into the document (bottom - <--INSERT--> )
    - Insert Mode -> Command Mode : Just press <u>ESC</u> 
- (Additional) Ex Mode
    - Special mode of Command mode
    - Search, Save, Replace, Move line, Quit
    - Ex Mode -> Command Mode : Just press <u>ESC</u> 

## Starting vi
- $vi
    - Start with new file
    - When you save this file, you should set the file name
- $vi filename
    - Open a file with vi
    - Ex) Type: vi myfile.txt
        - if myfile.txt does not exist, myfile.txt created
        - if myfile.txt does exist, the first few line of the file will appear.

## From Command Mode to Insert Mode
<table>
        <th>Key</th>
        <th>Actions</th>
        <tr>
            <td>i</td>
            <td>Insert text 'before' current character</td>
        </tr>
        <tr>
            <td>a</td>
            <td>Insert text 'after' current character</td>
        </tr>
        <tr>
            <td>I</td>
            <td>Begin text insertion at the "beginning of a line"</td>
        </tr>
        <tr>
            <td>A</td>
            <td>Begin text at "end of a line"</td>
        </tr>
        <tr>
            <td>o</td>
            <td>Open a new line 'below' current line</td>
        </tr>
        <tr>
            <td>O</td>
            <td>Open a new line 'above' current line</td>
        </tr>
        <tr>
            <td>s</td>
            <td>Substitute one character under cursor continue to insert</td>
        </tr>
        <tr>
            <td>S</td>
            <td>Substitute entire line and begin to insert at the beginning of the line</td>
        </tr>        
</table>

## Ex mode( Writing & Exiting in Command )
- Writing (Saving)
    <table>
    <th>Key</th>
    <th>Actions</th>
    <tr>
        <td>:w</td>
        <td>Save current file</td>
    </tr>
    <tr>
        <td>:w fileName</td>
        <td>Save current file to fileName</td>
    </tr>
    </table>
    
- Exiting vi
    <table>
    <th>Key</th>
    <th>Actions</th>
    <tr>
        <td>:q</td>
        <td>Quit(will only work if file has not been changed</td>
    </tr>
    <tr>
        <td>:q!</td>
        <td>Force quit</td>
    </tr>
    <tr>
        <td>:wq</td>
        <td>Save, then quit</td>
    </tr>
    <tr>
        <td>:wq fileName</td>
        <td>Save to fileName, then quit</td>
    </tr>
    </table>

## Command mode
- Basic Cursor Movement ( one line )
    - h(left), j(down), k(up), l(right)

    - w : Right one word(->, left to right)
    - b : Left one word(<-, right to left)
    - e : Start at the end of a word, left to right
    
- Advanced vi_1 (in command mode)
    - Deleting, and Changing Text 
    <table>
    <th>Key</th>
    <th>Actions</th>
    <tr>
        <td>x</td>
        <td>Delete a character</td>
    </tr>
    <tr>
        <td>X</td>
        <td>Backspace delete</td>
    </tr>
    <tr>
        <td>dd</td>
        <td>Delete a line, 10 + dd : delete 10 rows</td>
    </tr>
    <tr>
        <td>D</td>
        <td>Delete a line, But keep deleted rows intact</td>
    </tr>
    <tr>
        <td>r</td>
        <td>Replace a character</td>
    </tr>
    <tr>
        <td>R</td>
        <td>Edit mode (---REPLACE---)</td>
    </tr>
    <tr>
        <td>yy</td>
        <td>Copy row, 10 + yy : Copy 10 rows</td>
    </tr>
    <tr>
        <td>p</td>
        <td>Paste below by my cursor</td>
    </tr>
    <tr>
        <td>P</td>
        <td>Paste above by my cursor</td>
    </tr>
    </table>

- Advanced vi_2 (in command mode)
    <table>
    <th>Key</th>
    <th>Actions</th>
    <tr>
        <td>set nu</td>
        <td>Show line Numbers</td>
    </tr>
    <tr>
        <td>:set nonu</td>
        <td>Hide line numbers</td>
    </tr>
    <tr>
        <td>gg, [[</td>
        <td>Go to the beginning of the document</td>
    <tr>
        <td>G, ]]</td>
        <td>Go to the end of the document</td>
    </tr>
    <tr>
        <td>H</td>
        <td>Start of screen</td>
    </tr>
    <tr>
        <td>M</td>
        <td>Middle of screen</td>
    </tr>
    <tr>
        <td>L</td>
        <td>End of screen</td>
    </tr>
    <tr>
        <td>ctrl + b</td>
        <td>Go 'up' one page</td>
    </tr>
    <tr>
        <td>ctrl + f</td>
        <td>Go 'down' one page 'forward'</td>
    </tr>
    </table>

- Advanced vi_3(replacement : **치환**)
    - Form : :[number]s / [old content] / [new content]
    - (korean) : :줄번호 / 기존내용 / 바꿀 내용
        - :5s / passwd / security : Replace 5th 'passwd' with 'security'.
        - :20,23s / PASS / passport : Replace 20 ~ 23th 'PASS' with 'passport'.
        - :%s / MIN / MAX : Replace full document
        - **:numbers / old / new / g : replace at once** => Mainly used.

- shell command
    - :!ifconfig    : Stop vi and ifconfig ip address
    - :!            : Stop vi and print the working environment
    - :!command     : Stop vi and run the command
    - :1,3d         : delete 1 ~ 3rows

- etc
    - ctrl + w + n  : Divide the screen horizontally.
    - ctrl + w + o  : Close all windows except the one where I am.
    - ctrl + w + w  : Move the screen window.

    - :w            : save
    - :e            : open
    - :e [ file ]   : open the file
    - :enew          : make new file
    - :w >> [ file ] : Adds content to the specified file and saves it
    - :f            : indicates information.
        - ex) "file route" line 1 of 158 --0%-- col 1
## vim install & settup

- $ sudo apt-get install vim
- $ vi ~/.vimrc
    - set nu, set smartindent, set shftwidth=4, set laststatus=2, systanx on ...
