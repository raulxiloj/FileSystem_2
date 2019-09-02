%{
    #include <iostream>
    #include "parser.h"
    Nodo *raiz;
    char coment[400];
%}

%option case-insensitive
%option noyywrap

/*Regular expresions*/
letra [a-zA-Z]
entero ("-")?[0-9]+
caracter ({letra}|{entero})
id {letra}({letra}|{entero}|"_")*
cadena "\""[^"\""]*"\""
extension "."{id}
diagonal "/"
ruta ({diagonal}{id})+({diagonal}{id}{extension})

%x COM

%%
INITIAL
{
    "#"         { BEGIN COM; }

    "mkdisk"    { return mkdisk; }
    "rmdisk"    { return rmdisk; }
    "fdisk"     { return fdisk; }
    "mount"     { return mount; }
    "unmount"   { return unmount; }
    "rep"       { return rep; }
    "exec"      { return exec; }
    "-size"     { return size; }
    "-unit"     { return unit; }
    "-path"     { return path; }
    "-fit"      { return fit; }
    "-name"     { return name; }
    "-type"     { return type; }
    "-delete"   { return del; }
    "-add"      { return add; }
    "-id"       { return id; }
    "bf"        { return bf; }
    "ff"        { return ff; }
    "wf"        { return wf; }
    "Fast"      { return fast; }
    "Full"      { return full; }
    "mbr"       { return mbr; }
    "disk"      { return disk; }


    "mkfs"      { return mkfs; }
    "login"     { return login; }
    "logout"    { return logout; }
    "mkgrp"     { return mkgrp; }
    "rmgrp"     { return rmgrp; }
    "mkusr"     { return mkusr; }
    "rmusr"     { return rmusr; }
    "chmod"     { return chmod; }
    "mkfile"    { return mkfile; }
    "cat"       { return cat; }
    "rem"       { return rem; }
    "edit"      { return edit; }
    "ren"       { return ren; }
    "mkdir"     { return mkdir; }
    "cp"        { return cp; }
    "mv"        { return mv; }
    "find"      { return find; }
    "chown"     { return chown; }
    "chgrp"     { return chgrp; }
    "pause"     { return pause; }
    "recovery"  { return recovery; }
    "loss"      { return loss; }
    "-fs"       { return fs; }
    "-usr"      { return usr; }
    "-pwd"      { return pwd;  }
    "-grp"      { return grp; }
    "-ugo"      { return ugo; }
    "-r"        { return r; }
    "-p"        { return p; }
    "-cont"     { return cont; }
    "-file"     { return file; }
    "-dest"     { return dest; }
    "-ruta"     { return rutaRep; }
    "inode"     { return inode; }
    "journaling"{ return journaling; }
    "block"     { return block; }
    "bm_inode"  { return bm_inode; }
    "bm_block"  { return bm_block; }
    "tree"      { return tree; }
    "sb"        { return sb; }
    "file"      { return fileRep; }
    "ls"        { return ls; }


    "="         { return igual; }

    {entero}    {strcpy(yylval.text, yytext); return num;}
    {caracter}  {strcpy(yylval.text, yytext); return caracter;}
    {cadena}    {strcpy(yylval.text, yytext); return cadena;}
    {id}        {strcpy(yylval.text, yytext); return identificador;}
    {ruta}      {strcpy(yylval.text, yytext); return ruta;}
    {extension} {strcpy(yylval.text, yytext); return extension;}

    [[:blank:]] {}

    .            {std::cout <<yytext <<" Error Lexico" << std::endl;}
}

<COM>"\n"        { BEGIN INITIAL; /*strcpy(yylval.text, coment); memset(coment,0,400); return comentario;*/ };
<COM>.           { /*strcat(coment, yytext);*/ };

%%
