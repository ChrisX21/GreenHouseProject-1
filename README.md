# GreenHouseProject-1

## To run the programme:

### In the bottom status bar: 
Upload -> Serial Monitor

or

### In terminal:
```
pio run -t upload
pio device monitor -b 9600
```


## Git

### Get the latest changes
```
git fetch                    # download new commits and branches
git checkout <branch-name>   # switch to the branch (use master for the main one)
git pull                     # update it
```

### Upload your changes
```
git checkout master                  # start from the main branch
git pull                             # make sure it is up to date
git checkout -b <short-name>         # create your own branch
git status                           # check which files changed
git add .                            # stage all changes
git commit -m "Clear description of ch-ch-ch-ch-changes"
git push -u origin <short-name>      # first push of this branch
```
Later pushes on the same branch: `git push`

Then open a pull request into `master` on GitHub.