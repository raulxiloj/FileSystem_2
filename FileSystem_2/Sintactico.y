%{
    #include "scanner.h"
    #include "nodo.h"
    #include <iostream>

    extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
    extern Nodo *raiz; // Raiz del arbol

    int yyerror(const char* mens){
        std::cout<<mens<<std::endl;
        return 0;
    }

%}

%error-verbose

%union
    {
        char text[400];
        class Nodo *nodito;
    }

/*--------------Terminals-------------*/
%token <text> mkdisk
%token <text> rmdisk
%token <text> fdisk
%token <text> mount
%token <text> unmount
%token <text> rep
%token <text> exec
%token <text> size
%token <text> unit
%token <text> path
%token <text> fit
%token <text> name
%token <text> type
%token <text> del
%token <text> add
%token <text> id
%token <text> bf
%token <text> ff
%token <text> wf
%token <text> fast
%token <text> full
%token <text> mbr
%token <text> disk
%token <text> igual
%token <text> extension
%token <text> num
%token <text> caracter
%token <text> cadena
%token <text> identificador
%token <text> ruta

/*----------Not terminals------------*/
%type <nodito> INIT
%type <nodito> COMANDO
%type <nodito> MKDISK
%type <nodito> PARAMETRO_MK
%type <nodito> RMDISK
%type <nodito> FDISK
%type <nodito> PARAMETRO_FK
%type <nodito> MOUNT
%type <nodito> PARAMETRO_M
%type <nodito> UNMOUNT
%type <nodito> AJUSTE
%type <nodito> REP
%type <nodito> PARAMETRO_R
%type <nodito> SCRIPT

%start INIT

%%

INIT:  COMANDO { raiz = $$; };

COMANDO: mkdisk MKDISK {
                         $$ = new Nodo("MKDISK","");
                         $$->add(*$2);
                       }
         | RMDISK { $$ = $1; }
         | fdisk FDISK {
                          $$ = new Nodo("FDISK","");
                          $$->add(*$2);
                        }
         | mount MOUNT {
                         $$ = new Nodo("MOUNT", "");
                         $$->add(*$2);
                       }
         | UNMOUNT { $$ = $1; }
         | rep REP { $$ = new Nodo("REP","");
                     $$->add(*$2);
                   }
         | SCRIPT { $$ = $1; };



MKDISK: MKDISK PARAMETRO_MK {
                             $$ = $1;
                             $$->add(*$2);
                            }
        |PARAMETRO_MK {
                       $$ = new Nodo("PARAMETRO","");
                       $$->add(*$1);
                     };

PARAMETRO_MK: size igual num { $$= new Nodo("size",$3); }
            |fit igual AJUSTE {
                                $$ = new Nodo ("fit", "");
                                $$->add(*$3);
                               }
            |unit igual caracter { $$ = new Nodo("unit",$3); }
            |path igual cadena {
                                 $$ = new Nodo("path",$3);
                                }
            |path igual ruta {
                               $$ = new Nodo("path", $3);

                             };

RMDISK: rmdisk path igual ruta {
                                $$ = new Nodo("RMDISK","");
                                Nodo *n = new Nodo("path",$4);
                                $$->add(*n);
                               }
         | rmdisk path igual cadena {
                                      $$ = new Nodo("RMDISK","");
                                      Nodo *ruta = new Nodo("path",$4);
                                      $$->add(*ruta);
                                    };
FDISK: FDISK PARAMETRO_FK {
                            $$ = $1;
                            $$->add(*$2);
                          }
        | PARAMETRO_FK {
                        $$ = new Nodo("PARAMETRO","");
                        $$->add(*$1);
                      };

PARAMETRO_FK: PARAMETRO_MK { $$ = $1; }
              | type igual caracter { $$ = new Nodo("type",$3); }
              | del igual fast { $$ = new Nodo("delete", "fast"); }
              | del igual full { $$ = new Nodo("delete", "full"); }
              | name igual identificador { $$ = new Nodo("name", $3); }
              | name igual cadena { $$ = new Nodo("name", $3); }
              | add igual num { $$ = new Nodo("add", $3); };

MOUNT: MOUNT PARAMETRO_M {
                           $$ = $1;
                           $$->add(*$2);
                         }
       | PARAMETRO_M {
                        $$ = new Nodo("PARAMETRO","");
                        $$->add(*$1);
                      };

PARAMETRO_M: path igual cadena { $$ = new Nodo("path",$3); }
             | path igual ruta { $$ = new Nodo("path", $3); }
             | name igual identificador { $$ = new Nodo("name", $3); }
             | name igual cadena { $$ = new Nodo("name",$3); };

UNMOUNT: unmount id igual identificador {
                                          $$ = new Nodo("UNMOUNT", "");
                                          Nodo *n = new Nodo("id",$4);
                                          $$->add(*n);
                                        }

AJUSTE: bf { $$ = new Nodo("ajuste", "bf"); }
        | ff { $$ = new Nodo("ajuste", "ff"); }
        | wf { $$ = new Nodo("ajuste", "wf"); };


REP: REP PARAMETRO_R{
                     $$ = $1;
                     $$->add(*$2);
                    }
     | PARAMETRO_R{
                    $$ = new Nodo("PARAMETRO", "");
                    $$->add(*$1);
                  };

PARAMETRO_R: name igual mbr { $$ = new Nodo("name","mbr"); }
             | name igual disk { $$ = new Nodo("name","disk"); }
             | path igual cadena{ $$ = new Nodo("path", $3); }
             | path igual ruta {
                                $$ = new Nodo("path",$3);
                               }
             | id igual identificador {
                                        $$ = new Nodo("id", $3);
                                      };

SCRIPT: exec path igual cadena {
                                $$ = new Nodo("EXEC","");
                                Nodo *path = new Nodo("path", $4);
                                $$->add(*path);
                               }
        | exec path igual ruta {
                                 $$ = new Nodo("EXEC","");
                                 Nodo *n = new Nodo("path", $4);
                                 $$->add(*n);
                               };
