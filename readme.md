задачі для воротної автоматики:

1. опитування rf-приймача

2. опитування датчиків струму:
        - перенавантаження електромотору внаслідок механічної завади для
          відкриття-закриття воріт
        - відключеня електромоторів через пееренавантаження при упорі 
          створок в кінцеві упори в закритому і відкритому стані
3. керування моторами left leaf: D4;D5, right leaf: D6;D7. (пуск: (1,0), стоп: (0,0), реверс: (0,1)) 
        - приймає команди від радіопульта
        /*- приймає команди від кінцевиків*/
        - приймає команди від датчиків струму

Help:
        git --help
- Start arduino from folder arduino-1.8.10:
        andrei@E330 ~/arduino-1.8.10 $ ./arduino
- Enable acces to ttyUSB0:
        sudo chmod ugo+rw /dev/ttyUSB0
Git:
- Create remote repository:
- View pc ssh key for copy to github:
        cat ~/.ssh/id_rsa.pub
- Add remote repository:
        git remote add origin git@github.com:AndreiRadchenko/RF-Gate.git
- Add files and folders to local git:
        git add FreeRTOS/*
        git add readme.md
        git add uno-gate.sch
- View files under git:
        git ls-files
- Commit changes to current branch:
        git commit -a -m "change max load to 3A"
- Push commit to remote rep:
        git push -u origin master
- Create new branch and switch to this branch:
        git checkout -b current_sensors  

        git commit -a -m "change max load to 3A"
- View current changes from last commit:
        git diff
        git status
- Push new branch to remote repository:
        git push -u origin current_sensors
- Show all branches:
        git branch -a
- Switch to branch <current_sensors>:
        git checkout current_sensors
- Revert to previos commit without saving changes:
        git reset --hard HEAD~1
- Revert to 2 commit with saving changes:
        git reset --soft HEAD~2
- Viewing the Commit History of branch <master>
        git log master
        git log --pretty=oneline
         
        

