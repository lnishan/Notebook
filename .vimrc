set nocompatible

set enc=utf-8
set fenc=utf-8

set tabstop=4
set shiftwidth=4
set autoindent
set cindent

syntax on
set t_Co=256
colorscheme molokai 
set number
set showmatch

nmap <F9> :! g++ % -std=c++11 -O2 -Wall<CR> \| :! ./a.out<CR>
