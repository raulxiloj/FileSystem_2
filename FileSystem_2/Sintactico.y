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

%token <text> mkfs
%token <text> login
%token <text> logout
%token <text> mkgrp
%token <text> rmgrp
%token <text> mkusr
%token <text> rmusr
%token <text> Rchmod
%token <text> mkfile
%token <text> cat
%token <text> rem
%token <text> edit
%token <text> ren
%token <text> Rmkdir
%token <text> cp
%token <text> mv
%token <text> find
%token <text> Rchown
%token <text> chgrp
%token <text> pausa
%token <text> recovery
%token <text> loss
%token <text> fs
%token <text> fs2
%token <text> fs3
%token <text> usr
%token <text> pwd
%token <text> grp
%token <text> ugo
%token <text> r
%token <text> p
%token <text> cont
%token <text> file
%token <text> dest
%token <text> rutaRep
%token <text> inode
%token <text> journaling
%token <text> block
%token <text> bm_inode
%token <text> bm_block
%token <text> tree
%token <text> sb
%token <text> fileRep
%token <text> ls
%token <text> password
%token <text> directorio

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

%type <nodito> MKFS
%type <nodito> PARAM_MKFS
%type <nodito> LOGIN
%type <nodito> PARAM_LOGIN
%type <nodito> MKGRP
%type <nodito> RMGRP
%type <nodito> MKUSR
%type <nodito> PARAM_MKUSR
%type <nodito> RMUSR
%type <nodito> CHMOD
%type <nodito> PARAM_CHMOD
%type <nodito> MKFILE
%type <nodito> PARAM_MKFILE
%type <nodito> CAT
%type <nodito> REM
%type <nodito> EDIT
%type <nodito> PARAM_EDIT
%type <nodito> REN
%type <nodito> PARAM_REN
%type <nodito> MKDIR
%type <nodito> PARAM_MKDIR
%type <nodito> CP
%type <nodito> PARAM_CP
%type <nodito> MV
%type <nodito> FIND
%type <nodito> PARAM_FIND
%type <nodito> CHOWN
%type <nodito> PARAM_CHOWN
%type <nodito> CHGRP
%type <nodito> PARAM_CHGRP
%type <nodito> RECOVERY
%type <nodito> LOSS
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
         | SCRIPT { $$ = $1; }
         | mkfs MKFS {
                        $$ = new Nodo("MKFS","");
                        $$->add(*$2);
                     }
         | login LOGIN {
                         $$ = new Nodo("LOGIN", "");
                         $$->add(*$2);
                       }
         | logout { $$ = new Nodo("LOGOUT",""); }
         | MKGRP { $$ = $1; }
         | RMGRP { $$ = $1; }
         | mkusr MKUSR {
                        $$ = new Nodo("MKUSR","");
                        $$->add(*$2);
                       }
         | RMUSR { $$ = $1; }
         | Rchmod CHMOD {
                         $$ = new Nodo("CHMOD","");
                         $$->add(*$2);
                       }
         | mkfile MKFILE {
                            $$ = new Nodo("MKFILE","");
                            $$->add(*$2);
                         }
         | CAT { $$ = $1; }
         | REM { $$ = $1; }
         | edit EDIT {
                       $$ = new Nodo("EDIT","");
                       $$->add(*$2);
                     }
         | ren REN{
                    $$ = new Nodo("REN","");
                    $$->add(*$2);
                  }
         | Rmkdir MKDIR{
                        $$ = new Nodo("MKDIR","");
                        $$->add(*$2);
                      }
         | cp CP{
                  $$ = new Nodo("CP","");
                  $$->add(*$2);
                }
         | mv MV{
                  $$ = new Nodo("MV","");
                  $$->add(*$2);
                }
         | find FIND{
                      $$ = new Nodo("FIND","");
                      $$->add(*$2);
                    }
         | Rchown CHOWN{
                        $$ = new Nodo("CHOWN","");
                        $$->add(*$2);
                      }
         | chgrp CHGRP{
                        $$ = new Nodo("CHGRP","");
                        $$->add(*$2);
                      }
         | pausa { $$ = new Nodo("PAUSE",""); }
         | RECOVERY { $$ = $1; };
         | LOSS { $$ = $1; }
         ;



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
             | name igual inode { $$ = new Nodo("name", "inode"); }
             | name igual journaling { $$ = new Nodo("name", "journaling"); }
             | name igual block { $$ = new Nodo("name", "block"); }
             | name igual bm_inode { $$ = new Nodo("name", "bm_inode"); }
             | name igual bm_block { $$ = new Nodo("name", "bm_block"); }
             | name igual tree { $$ = new Nodo("name", "tree"); }
             | name igual sb { $$ = new Nodo("name", "sb"); }
             | name igual fileRep { $$ = new Nodo("name", "file"); }
             | name igual ls { $$ = new Nodo("name", "ls"); }
             | path igual cadena{ $$ = new Nodo("path", $3); }
             | path igual ruta { $$ = new Nodo("path",$3); }
             | id igual identificador { $$ = new Nodo("id", $3); }
             | rutaRep igual ruta { $$ = new Nodo("ruta", $3); }
             | rutaRep igual cadena { $$ = new Nodo("ruta", $3); };

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

MKFS: MKFS PARAM_MKFS {
                        $$ = $1;
                        $$->add(*$2);
                      }
      | PARAM_MKFS {
                      $$ = new Nodo("PARAMETRO", "");
                      $$->add(*$1);
                   };

PARAM_MKFS: id igual identificador { $$ = new Nodo("id",$3); }
            | type igual fast { $$ = new Nodo("type", "fast"); }
            | type igual full { $$ = new Nodo("type", "full"); }
            | fs igual fs2 { $$ = new Nodo("fs", "2fs"); }
            | fs igual fs3 { $$ = new Nodo("fs", "3fs"); };

LOGIN: LOGIN PARAM_LOGIN {
                           $$ = $1;
                           $$->add(*$2);
                         }
       | PARAM_LOGIN {
                        $$ = new Nodo("PARAMETRO","");
                        $$->add(*$1);
                     };

PARAM_LOGIN: usr igual identificador { $$ = new Nodo("user", $3); }
            | usr igual cadena { $$ = new Nodo("user", $3); }
            | pwd igual num { $$ = new Nodo("password",$3); }
            | pwd igual identificador { $$ = new Nodo("password", $3); }
            | pwd igual password { $$ = new Nodo("password", $3); }
            | pwd igual cadena { $$ = new Nodo("password", $3); }
            | id igual identificador { $$ = new Nodo("id", $3); };

MKGRP: mkgrp name igual identificador {
                                        $$ = new Nodo("MKGRP","");
                                        Nodo *n = new Nodo("name",$4);
                                        $$->add(*n);
                                      }
       | mkgrp name igual cadena {
                                    $$ = new Nodo("MKGRP","");
                                    Nodo *n = new Nodo("name",$4);
                                    $$->add(*n);
                                 };

RMGRP: rmgrp name igual identificador {
                                        $$ = new Nodo("RMGRP","");
                                        Nodo *n = new Nodo("name", $4);
                                        $$->add(*n);
                                     }
       | rmgrp name igual cadena {
                                    $$ = new Nodo("RMGRP", "");
                                    Nodo *n = new Nodo("name",$4);
                                    $$->add(*n);
                                 };
MKUSR: MKUSR PARAM_MKUSR {
                           $$ = $1;
                           $$->add(*$2);
                         }
       | PARAM_MKUSR {
                        $$ = new Nodo("PARAMETRO", "");
                        $$->add(*$1);
                     };

PARAM_MKUSR: usr igual identificador { $$ = new Nodo("user",$3); }
             | usr igual cadena { $$ = new Nodo("user",$3); }
             | pwd igual num { $$ = new Nodo("password",$3); }
             | pwd igual identificador { $$ = new Nodo("password", $3); }
             | pwd igual password { $$ = new Nodo("password", $3); }
             | pwd igual cadena { $$ = new Nodo("password",$3); }
             | grp igual identificador { $$ = new Nodo("group", $3); };

RMUSR: rmusr usr igual identificador {
                                        $$ = new Nodo("RMUSR","");
                                        Nodo *n = new Nodo("user",$4);
                                        $$->add(*n);
                                     }
      | rmusr usr igual cadena {
                                  $$ = new Nodo("RMUSR", "");
                                  Nodo *n = new Nodo("user",$4);
                                  $$->add(*n);
                               };

CHMOD: CHMOD PARAM_CHMOD {
                          $$ = $1;
                          $$->add(*$2);
                         }
       | PARAM_CHMOD {
                       $$ = new Nodo("PARAMETRO","");
                       $$->add(*$1);
                     };

PARAM_CHMOD: path igual cadena { $$ = new Nodo("path",$3); }
            | path igual directorio { $$ = new Nodo("path",$3); }
            | ugo igual num { $$ = new Nodo("ugo",$3); }
            | r { $$ = new Nodo("r",""); };

MKFILE: MKFILE PARAM_MKFILE {
                              $$ = $1;
                              $$->add(*$2);
                            }
        | PARAM_MKFILE{
                        $$ = new Nodo("PARAMETRO","");
                        $$->add(*$1);
                      };


PARAM_MKFILE: path igual ruta { $$ = new Nodo("path",$3); }
              | path igual cadena { $$ = new Nodo("path",$3); }
              | size igual num { $$ = new Nodo("size",$3); }
              | cont igual ruta { $$ = new Nodo("cont",$3); }
              | cont igual cadena { $$ = new Nodo("cont",$3); }
              | p { $$ = new Nodo("p",""); };

CAT: cat file igual ruta{
                          $$ = new Nodo("CAT","");
                          Nodo *n = new Nodo("file",$4);
                          $$->add(*n);
                        }
    | cat file igual cadena{
                             $$ = new Nodo("CAT","");
                             Nodo *n = new Nodo("file",$4);
                             $$->add(*n);
                           };

REM: rem path igual ruta{
                          $$ = new Nodo("REM","");
                          Nodo *n = new Nodo("path",$4);
                          $$->add(*n);
                        }
     | rem path igual cadena{
                               $$ = new Nodo("REM","");
                               Nodo *n = new Nodo("path",$4);
                               $$->add(*n);
                            };

EDIT: EDIT PARAM_EDIT {
                        $$ = $1;
                        $$->add(*$2);
                      }
      | PARAM_EDIT {
                     $$ = new Nodo("PARAMETRO","");
                     $$->add(*$1);
                   };

PARAM_EDIT: path igual ruta { $$ = new Nodo("path",$3); }
            | path igual cadena { $$ = new Nodo("path",$3); }
            | cont igual cadena { $$ = new Nodo("cont", $3); };

REN: REN PARAM_REN {
                    $$ = $1;
                    $$->add(*$2);
                   }
     | PARAM_REN {
                   $$ = new Nodo("PARAMETRO","");
                   $$->add(*$1);
                 };

PARAM_REN: path igual ruta { $$ = new Nodo("path", $3); }
           | path igual cadena { $$ = new Nodo("path",$3); }
           | name igual identificador extension {
                                                  $$ = new Nodo("name","");
                                                  Nodo *n = new Nodo($3,$4);
                                                  $$->add(*n);
                                                }
           | name igual cadena { $$ = new Nodo("name",$3); };

MKDIR: MKDIR PARAM_MKDIR {
                           $$ = $1;
                           $$->add(*$2);
                         }
       | PARAM_MKDIR{
                      $$ = new Nodo("PARAMETRO","");
                      $$->add(*$1);
                    };

PARAM_MKDIR: path igual ruta { $$ = new Nodo("path",$3); }
             | path igual cadena { $$ = new Nodo("path",$3); }
             | id igual identificador { $$ = new Nodo("id",$3);}
             | p { $$ = new Nodo("p",""); };

CP: CP PARAM_CP{
                 $$ = $1;
                 $$->add(*$2);
               }
    | PARAM_CP{
                $$ = new Nodo("PARAMETRO","");
                $$->add(*$1);
              };

PARAM_CP: path igual ruta { $$ = new Nodo("path",$3); }
          | path igual cadena { $$ = new Nodo("path",$3); }
          | dest igual ruta { $$ = new Nodo("dest",$3); }
          | dest igual cadena { $$ = new Nodo("dest",$3); };

MV: MV PARAM_CP {
                  $$ = $1;
                  $$->add(*$2);
                }
    | PARAM_CP{
                $$ = new Nodo("PARAMETRO","");
                $$->add(*$1);
              };

FIND: FIND PARAM_FIND {
                        $$ =$1;
                        $$->add(*$2);
                      }
      | PARAM_FIND {
                     $$ = new Nodo("PARAMETRO","");
                     $$->add(*$1);
                   };

PARAM_FIND: path igual ruta { $$ = new Nodo("path",$3); }
            | path igual cadena { $$ = new Nodo("path",$3); }
            | name igual id extension {
                                        $$ = new Nodo("name","");
                                        Nodo *n = new Nodo($3,$4);
                                        $$->add(*n);
                                      }
            | name igual cadena { $$ = new Nodo("name",$3); };

CHOWN: CHOWN PARAM_CHOWN {
                           $$ = $1;
                           $$->add(*$2);
                         }
       | PARAM_CHOWN {
                       $$ = new Nodo("PARAMETRO","");
                       $$->add(*$1);
                     };

PARAM_CHOWN: path igual ruta { $$ = new Nodo("path",$3); }
             | path igual cadena { $$ = new Nodo("path", $3); }
             | usr igual identificador { $$ = new Nodo("user",$3); }
             | usr igual cadena { $$ = new Nodo("user",$3); }
             | r { $$ = new Nodo("r",""); };

CHGRP: CHGRP PARAM_CHGRP {
                           $$ = $1;
                           $$->add(*$2);
                         }
       | PARAM_CHGRP{
                      $$ = new Nodo("PARAMETRO","");
                      $$->add(*$1);
                    };

PARAM_CHGRP: usr igual identificador { $$ = new Nodo("user",$3); }
             | usr igual cadena { $$ = new Nodo("user",$3); }
             | grp igual identificador { $$ = new Nodo("group",$3);}
             | grp igual cadena { $$ = new Nodo("group", $3); };

RECOVERY: recovery id igual identificador {
                                            $$ = new Nodo("RECOVERY","");
                                            Nodo *n = new Nodo("id",$4);
                                            $$->add(*n);
                                          };

LOSS: loss id igual identificador{
                                    $$ = new Nodo("LOSS","");
                                    Nodo *n = new Nodo("id",$4);
                                    $$->add(*n);
                                 };
