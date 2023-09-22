# 4th

**`4th`** is a simple interpreter of `forth` scripts, written in `C`.
This projet was created from scratch with the university project booklet (in [`docs/sources/proj-sem-impair-2022-2023/v2.pdf`](https://github.com/one-dev-man/4th/blob/main/docs/proj-sem-impair-2022-2023/v2.pdf))

## Build :

You can build the project binary with **`make`** and find it in the `dist` directory.

## Usage :

**`4th`** is a CLI application, so you need to specify it some arguments :

| Option | Description | Usage example |
| :----- | :---------- | :------------ |
|  |  |  |
| `--basic` | Use the interpreter in `basic` intepretation mode (level 1) | `4th --basic ./test-basic.forth` |
| `--medium` | Use the interpreter in `medium` intepretation mode (level 2) | `4th --medium ./test-medium.forth` |
| `--normal` | Use the interpreter in `normal` intepretation mode (level 3) | `4th --normal ./test-normal.forth` |
| `--advanced` | Use the interpreter in `advanced` intepretation mode (level 4 and default mode) | `4th --advanced ./test-advanced.forth` |
|  |  |  |
| `--debug` | Specify to the interpreter to be in `debug` mode. | `4th --advanced --debug ./myscript.forth` |
|  |  |  |

The basic usage is : `4th <program_filepath>`

### Play with 4th ! :

To test **`4th`**, clone this repository and try to run the script [`resources/samples/tictactoe/main.forth`](https://github.com/one-dev-man/4th/blob/main/resources/samples/tictactoe/main.forth), and as its name suggests, it's a simple **tictactoe** written in `forth` (please be indulgent, there is some bugs in the gameplay).

<hr>

#### Author(s) :

<div style="float:left;margin:0 10px 10px 0">
    <img align="left" src="https://contrib.rocks/image?repo=one-dev-man/4th" width="24px">
    <a href="https://github.com/one-dev-man/">
        OneDevMan
    </a>
</div>