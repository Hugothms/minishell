# minishell

The objective of this project is to create a simple shell like bash or zsh 


![Minishell-gif][minishell-gif]

[![hthomas' 42 Project Score](https://badge42.herokuapp.com/api/project/hthomas/minishell)](https://github.com/JaeSeoKim/badge42)

## Usage

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
[minishell-gif]: https://github.com/Hugothms/minishell/blob/master/minishell.gif

