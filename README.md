# minishell

The objective of this project is to create a simple shell like bash or zsh 


![Minishell-gif][minishell-gif]

[![hthomas's 42 minishell Score](https://badge42.vercel.app/api/v2/cl1m0540e000609mon8jcubug/project/1940032)](https://github.com/JaeSeoKim/badge42)

## Usage
First clone the repository and the git submodules:

    git clone --recurse-submodules git@github.com:Hugothms/minishell.git

Then make and run the executable:

    make && ./minishell

Or, more conveniently:

    make run

## Features
### ✅ It supports:
* all bash commands
* `'` and `"` like in bash
* `;` to separate the commands
* `|` to link the output of a command on the input of another one
* `<`, `>` and `>>` to manage redirections of a command
* `$` to replace by the assiociated environment variable
* `ctrl-C`, `ctrl-D` and `ctrl-\` have the same result as in bash

### ❌ It doesn't support:
* multi lines commands
* many other things 🤷🏻‍♂️

## Collaborators
This project was developed in team with [@Dicayne][dicayne] (Victor Moreau)

[dicayne]: https://github.com/Dicayne
[minishell-gif]: https://github.com/Hugothms/minishell/blob/master/demo-minishell.gif

