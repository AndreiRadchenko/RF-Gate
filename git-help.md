### Arduino Help:
- Start arduino from folder arduino-1.8.10:

        andrei@E330 ~/arduino-1.8.10 $ ./arduino
        
- Enable acces to ttyUSB0:

        sudo chmod ugo+rw /dev/ttyUSB0
        
### Git help:
- Create remote reposit
- Generating a new SSH key:

       $ ssh-keygen -t ed25519 -C "your_email@example.com"

- Adding your SSH key to the ssh-agent:

       $ eval "$(ssh-agent -s)"
       $ ssh-add ~/.ssh/id_ed25519

- Add your SSH key from <user>/.ssh/id_ed25519.pub to github
- View pc ssh key for copy to github:

       cat ~/.ssh/id_rsa.pub

- Create a new repository on the command line

        echo "# WebMicGain" >> README.md
        git init
        git add README.md
        git commit -m "first commit"
        git remote add origin git@github.com:AndreiRadchenko/WebMicGain.git
        git push -u origin master
        
- Add remote repository:

        git remote add origin git@github.com:AndreiRadchenko/RF-Gate.git
        
- If $ git pull origin [repo]
fatal: refusing to merge unrelated histories, try 
        
        $ git pull origin [repo] --allow-unrelated-histories

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

- Pull from remote repository:

        git pull
        git merge <branch>

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

- To show all of the tracked files that have been committed (on the current branch), use

        git ls-tree --full-tree --name-only -r HEAD
        
        --full-tree makes the command run as if you were in the repo's root directory.
        -r recurses into subdirectories. Combined with --full-tree, this gives you all committed, tracked files.
        --name-only removes SHA / permission info for when you just want the file paths.
        HEAD specifies which branch you want the list of tracked, committed files for. You could change this to master or any other branch name, but HEAD is the commit you have checked out right now.
        
- Downloads new changes from the branch named master on the remote named origin and integrates them into your local HEAD branch.
        
        git pull origin master
        
- If your have no access to git.hub over ssh:
        
        sudo nano ~/.ssh/config
        
  add next strigs:
        
        Host github.com
         Hostname ssh.github.com
         Port 443

  to check connection:
        
        ssh -T git@github.com
        
- To change remote repositoriy:
        
        git remote set-url origin git@github.com:<Username>/<Project>.git
