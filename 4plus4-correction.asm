BITS 64
global _start

section .text
_start:
mov r12, 0x4         ; Mettre 4 dans r12
mov r13, 0x4
add r12, r13          ; ajouter à r12 le contenu de r13

; on affiche
mov al, 0x1         ; on prépare notre sys_write
mov rdi, 0x1        ; affichage STDOUT, soit le terminal
add r12, 0x30        ; POUR AFFICHAGE ASCII OK (cf. man ascii)
push r12             ; on push r12 sur la STACK
mov rsi, rsp        ; on met le pointeur de stack dans rsi (source d'affichage)
mov rdx, 0x1        ; longeur de chaine à imprimer
syscall
mov rcx, 0x0A       ; \n en hexa, soit nouvelle ligne
push rcx            ; on le met sur la stack
mov rsi, rsp        ; on indique le dernier élément de la stack en source pour le sys_write
syscall
jmp _fin            ; on passe au label (la fonction) "_fin"

; Fermer proprement
_fin:
mov rax, 60         ; sys_exit
mov rdi, 0          ; exit_success (le programme s'est déroulé sans erreurs)
syscall


