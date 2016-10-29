let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/Documents/TerminalTuner/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +36 ~/Documents/TerminalTuner/src/TerminalTuner.cpp
badd +63 ~/Documents/TerminalTuner/src/recordaudio.cpp
badd +1 ~/Documents/TerminalTuner/src/Session.vim
badd +23 term://.//2030:/usr/bin/zsh
badd +187 ~/.config/nvim/init.vim
badd +0 term://.//2115:/usr/bin/zsh
argglobal
silent! argdel *
argadd TerminalTuner.cpp
edit ~/Documents/TerminalTuner/src/TerminalTuner.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 46 + 37) / 74)
exe 'vert 1resize ' . ((&columns * 136 + 136) / 273)
exe '2resize ' . ((&lines * 24 + 37) / 74)
exe 'vert 2resize ' . ((&columns * 136 + 136) / 273)
exe 'vert 3resize ' . ((&columns * 136 + 136) / 273)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal nofen
silent! normal! zE
let s:l = 42 - ((26 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
42
normal! 012|
wincmd w
argglobal
edit term://.//2115:/usr/bin/zsh
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 24 - ((23 * winheight(0) + 12) / 24)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
24
normal! 0
wincmd w
argglobal
edit ~/Documents/TerminalTuner/src/TerminalTuner.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal nofen
silent! normal! zE
let s:l = 42 - ((41 * winheight(0) + 35) / 71)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
42
normal! 09|
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 46 + 37) / 74)
exe 'vert 1resize ' . ((&columns * 136 + 136) / 273)
exe '2resize ' . ((&lines * 24 + 37) / 74)
exe 'vert 2resize ' . ((&columns * 136 + 136) / 273)
exe 'vert 3resize ' . ((&columns * 136 + 136) / 273)
tabnext 1
if exists('s:wipebuf') && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
