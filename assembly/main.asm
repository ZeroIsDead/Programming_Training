%define BOOK_MAX_SIZE 5
%define BOOK_SIZE 20

section .data                   ; Data segment (initialized data)
    system_title_text db "Library Management System"
    system_title_text_len equ $ - system_title_text

    clear_screen_sequence db 0x1b, "[H", 0x1b, "[J"
    clear_screen_len equ $ - clear_screen_sequence

    file db "books.txt"
    file_name_len equ $ - file

    menu_choices db "1. Add Book", 10, "2. Borrow book", 10, "3. Return Book", 10, "4. Exit Program", 10
    menu_len equ $ - menu_choices

    query_user db "Enter an Input: "
    qu_len equ $ - query_user

    invalid_msg db "Invalid Input!", 10
    invalid_msg_len equ $ - invalid_msg
    
    add_book_query db "Enter the Book Title You Want to Add: "
    add_book_query_len equ $ - add_book_query

    invalid_add_book_query db "The Book already Exists!", 10
    invalid_add_book_query_len equ $ - invalid_add_book_query
    
    borrow_book_query db "Enter the Book Title You Want to Borrow: "
    borrow_book_query_len equ $ - borrow_book_query

    borrow_book_menu_text db "These are the Books Available to Borrow: "
    borrow_book_menu_text_len equ $ - borrow_book_menu_text

    invalid_borrow_book_query db "The Book is not present!", 10
    invalid_borrow_book_query_len equ $ - invalid_borrow_book_query

    return_book_menu_text db "These are the Books that haven't Been Returned:", 10
    return_book_menu_len equ $ - return_book_menu_text

    return_book_query db "Enter the Book Title You Want to Return: "
    return_book_query_len equ $ - return_book_query

    invalid_return_book_query db "The Book is Not Recorded By The Library!", 10
    invalid_return_book_query_len equ $ - invalid_return_book_query

    return_to_menu_query db "Return to Menu (Y|N): "
    return_to_menu_query_len equ $ - return_to_menu_query


section .bss                        ; BSS segment (uninitialized data)
    buffer resb 256                             ; Reserve 256 bytes 
    books resb 100                              ; 5 x 20 bytes (Each book 19 bytes and 1 byte for stock - number available) 
    books_stock_available resb BOOK_MAX_SIZE    ; Number of each book available in the system
    books_stock_borrowed resb BOOK_MAX_SIZE     ; Number of each book borrowed
    current_book_index resb 1                   ; index of current book
    book_num resb 1                             ; Number of Book in the array / array length
    inputBuffer resb 100                        ; buffer for user input - Reads all 100 bytes regardless
    input resb 100                              ; current user input - assume a line is one input - stores one line/current user input

section .text               ; Code segment
    global _start       ; Entry point for linker (Linux) or main (Windows)

print_string: ; assumes string address and length in ecx and edx respectively
    pusha ; push all registers onto stack

    mov eax, 4
    mov ebx, 1
    int 0x80

    popa
    ret

%macro PRINT_STR 2      ; takes 2 parameters: string label, length
    pusha ; push all registers onto stack
    mov ecx, %1
    mov edx, %2
    call print_string
    popa
%endmacro

%macro JMP_TO_SUB_MENU_ON_COND 2 ; assume one byte (choice) found in al register
    cmp al, %1
    je %2
%endmacro

_start:
    call main_menu
    ; restart
    jmp exit_program

get_input_from_buffer: ; assume string is stored in edi, place line into input var
    push eax
    push ecx

    .copy_from_buffer:
        mov al, [edi]
        mov [input + ecx], al
        inc edi
        inc ecx

        cmp al, 10  ; if newline
        je .get_input_from_buffer_finish
        cmp al, 0   ; if terminal char
        je .get_input_from_buffer_finish
        cmp al, 13  ; if carriage return
        je .get_input_from_buffer_finish

        jmp .copy_from_buffer


    .get_input_from_buffer_finish:
        pop ecx
        pop eax

        ret


get_len:  ; String stored in edi, returns len at edx
    push ecx
    xor ecx, ecx ; reset to 0

    .len_loop:
        cmp [edi], byte 10              ; newline?
        je .done_len
        cmp [edi], byte 0               ; Terminating character?
        je .done_len

        inc edi
        inc ecx
        cmp ecx, 100                    ; max 100 char
        jne .len_loop

    .done_len:
        mov edx, ecx
        pop ecx

    ret


strip_newline: ; assumes string address at edi, returns clean string at esi
    push esi

    mov esi, edi

    .skip_unwanted_char:
        mov al, [edi]
        cmp al, 20  ; if space char
        je .skip_next
        cmp al, 10  ; if new line
        je .skip_next
        cmp al, 0   ; if terminal char
        je .strip_finished

        jmp .strip_finished

    .skip_next:
        inc edi
        jmp .skip_unwanted_char


    .strip_finished:
        mov al, [edi]       ; move char to temporary register
        mov [esi], al       ; shift 
        inc edi             ; next index
        inc esi             ; next index
        
        cmp byte [edi], 0        ; if terminal char
        jne .strip_finished  ; shift again

        mov byte [esi], 0        ; null-terminate the string
        mov edi, esi

        pop esi
        ret
read_file: ; ; open and read book txt
    mov eax, 5
    mov ebx, file
    mov ecx, 0
    mov edx, 0
    int 0x80

    mov ebx, eax
    call clear_inputBuffer

    mov eax, 3
    mov ecx, inputBuffer
    mov edx, 100
    int 0x80

    ; eax stores num bytes read
    ret

clear_inputBuffer: ; cleans input buffer var
    push ecx
    push edi
    push eax

    mov ecx, 100
    mov edi, inputBuffer
    mov al, 0

    rep stosb  ; write 0 to edi 100 times

    pop eax
    pop edi
    pop ecx
    ret


initialize_book_array: ; read from text file and places saved books into array
    call read_file  ; inputBuffer stores the line, eax stores the n bytes read

    


    call close_file

close_file: ; close the book txt
    pusha
    mov eax, 6
    int 0x80
    popa
check_buffer_has_content: ; returns code in al register (1 0 has, 0 - no content)
    mov eax, [inputBuffer]
    cmp eax, 0
    je .doesnt_have_content
    cmp eax, 10
    je .doesnt_have_content
    cmp eax, 13
    je .doesnt_have_content


    .has_content:
        xor eax, eax
        mov al, 1   ; code 1 - has content
        ret

    .doesnt_have_content:
        xor eax, eax
        mov al, 0   ; code 0 - no content
        ret
read_line: ; read the entire stdin (100 bytes) - store in input var
    pusha

    ; if input Buffer still have content then get current Input
    .check_buffer_content:
        call check_buffer_has_content 
        cmp al, 1
        je .get_current_input ; if has content, do not call read but take next line from inputBuffer

    .clear_and_read:
        call clear_inputBuffer

        mov eax, 3              ; syscall: read
        mov ebx, 0              ; stdin
        mov ecx, inputBuffer    ; buffer to store input
        mov edx, 100            ; number of bytes to read
        int 0x80                 ; input stored in inputBuffer

    .get_current_input:
        mov edi, inputBuffer
        call strip_newline
        call get_input_from_buffer

    .validation:             ; if the content of the input is garbage, then read again
        cmp byte [edi], 10   ; if new line
        je .check_buffer_content
        cmp byte [edi], 0    ; if terminal char
        je .check_buffer_content
        cmp byte [edi], 13    ; if carriage return char
        je .check_buffer_content

    popa
    ret
get_user_input: ; prints query (expected at ecx) and length at (edx) and read the line - store in input var
    PRINT_STR ecx, edx
    call read_line
    ret

%macro ASK_AND_READ 2 ; query and query length
    pusha

    mov ecx, %1
    mov edx, %2
    call get_user_input

    popa
%endmacro

main_menu:
    call print_menu
    ASK_AND_READ query_user, qu_len

    ; If Match then Jump
    ; uses conditional jump - so only can jump to local labels
    mov al, [input]
    JMP_TO_SUB_MENU_ON_COND '1', .add_book_section
    JMP_TO_SUB_MENU_ON_COND '2', .borrow_book_section
    JMP_TO_SUB_MENU_ON_COND '3', .return_book_section
    JMP_TO_SUB_MENU_ON_COND '4', .exit_program_section

    .add_book_section:
        jmp add_book_menu

    .borrow_book_section:
        jmp borrow_book_menu

    .return_book_section:
        jmp return_book_menu

    .exit_program_section:
        jmp exit_program

    ; No match then Invalid and Print Again
    PRINT_STR invalid_msg, invalid_msg_len 
    jmp main_menu

clear_screen:
    PRINT_STR clear_screen_sequence, clear_screen_len
    ret

print_menu:
    ; clear screen then 
    ; call clear_screen - no need to clear screen first
    PRINT_STR menu_choices, menu_len
    ret

add_book_menu:
    ; input book title
    ; store in memory
    ; update count
    ASK_AND_READ add_book_query, add_book_query_len  ; Ask query and read line - place in Input

    mov edi, input

    call get_len ; expects string at edi, returns edx

    .valid_book_check_1:
        ; Jump to Invalid Book if Length of Title > 20
        cmp edx, 20      
        jg .invalid_book

    .valid_book_check_2:
        mov esi, input

        mov al, [book_num]
        cmp al, 5
        jle .valid_book ; if the book array is still not full then the book is valid

        call book_exist ; returns the index of the book in al register

        cmp al, 5; if index is 5 (more than max length) then invalid
        je .invalid_book

        jmp .valid_book

    .invalid_book:
        ; Print Invalid then Retry
        PRINT_STR invalid_add_book_query, invalid_add_book_query_len
        jmp add_book_menu

    ; if book is valid then add the book
    .valid_book:
       call add_book

    .again:
        ; ASK_AND_READ - if want to continue again?
        cmp al, 0
        je borrow_book_menu

    jmp main_menu
borrow_book_menu:
    PRINT_STR borrow_book_menu_text, borrow_book_menu_text_len

    ; call print_available_books

    ASK_AND_READ borrow_book_query, borrow_book_query_len
    
    mov edi, input  ; place input as parameter for book_exist
    call book_exist ; check if book exist

    cmp al, 5
    je .no_book_found

    .book_found:
        call borrow_book

    .no_book_found:
        PRINT_STR invalid_borrow_book_query, invalid_add_book_query_len

    .again:
        ; ASK_AND_READ - if want to continue again?
        cmp al, 0
        je borrow_book_menu

    jmp main_menu

return_book_menu:
    jmp main_menu

compare_string: ; stringA - edi, stringB - esi, size - ecx, returns bool at dl 
    push ecx
    push eax
    push esi
    push edi

    mov al, [edi]
    cmp al, [esi]
    jne .not_equal

    cmp al, 0       ; if null char
    je .equal
    cmp al, 10      ; if new line
    je .equal 
    
    inc edi
    inc esi
    dec ecx

    cmp ecx, 0      ; if all char match until size limit
    je .equal

    .not_equal:
        mov al, 0

    .equal:
        mov al, 1


    pop edi
    pop esi
    pop eax
    pop ecx
    ret

%macro COMPARE_BOOK 3 ; takes in BookA, BookB, and size (Assumes that the size of both is always the same, otherwise they are different)
    pusha
    mov edi, %1
    mov esi, %2
    mov ecx, %3
    call compare_string
    popa
%endmacro


update_book_array: ; title- esi, length - dh, num - ah, index - dl 
    pusha

    xor ecx, ecx
    movzx ecx, dl       ; index of book

    call get_book_at_index  ; expects index at ecx and returns book as edi

    movzx ecx, dh         ; length of string

    .copy_loop:
        mov al, [esi]
        mov [edi], al
        inc esi
        inc edi
        dec ecx
        cmp al, 0 ; if null
        je .update_count
        cmp al, 10 ; if new line
        je .update_count
        cmp ecx, 0 ; if length at 0
        je .update_count
        
        jmp .copy_loop

    .update_count:
        movzx ecx, dl        ; move index 
        mov [edi + ecx], ah       ; Update Num of Books in Array

    popa

get_book_at_index: ; index at ecx and returns address of book in edi
    mov edi, books
    imul ecx, 20             ; multiply by 20
    add edi, ecx             ; move to correct Book



book_exist: ; book title at esi - returns index at al register
    push ecx
    push edi

    xor cl, cl ; index - set to 0
    xor ch, ch   ; current index in string - set to 0

    cmp cl, [book_num] ; checks if number of books in the system matches the current index
    je .book_not_found

    call get_book_at_index ; get book at edi

    .book_comparison_loop:
        COMPARE_BOOK esi, edi, BOOK_SIZE
        cmp dl, 1
        je .book_found

    .next_book:
        inc cl
        cmp cl, [book_num]
        je .book_not_found

        call get_book_at_index ; get book at edi
        jl .book_comparison_loop


    .book_found:
        mov al, cl ; index - if not found then ecx == 5

        pop edi
        pop ecx
        ret

    .book_not_found:
        mov al, 5

        pop edi
        pop ecx
        ret

add_book: ; Assume Length is in edx, Title is in edi, and index at al
    pusha

    mov edi, books_stock_available      ; move the address of the books_stock seg
    movzx ecx, al                       ; move the wanted book's Index to 32-bit reg
    add edi, ecx                        ; move to the wanted book's Index
    mov ah, [edi]                       ; get Number of Books with the Title in the System

    ; Title, Length, Number of Books, Index in Array
    call update_book_array

    popa
    ret

borrow_book: ; book title at edi - assume that all validation checks (title is valid) are done
    ; input book ID
    ; check if available
    ; mark as borrowed
    ; PRINT_STR borrow

    pusha

; buffer resb 256                             ; Reserve 256 bytes 
;     books resb 100                              ; 5 x 20 bytes (Each book 19 bytes and 1 byte for stock - number available) 
;     books_stock_available resb BOOK_MAX_SIZE    ; Number of each book available in the system
;     books_stock_borrowed resb BOOK_MAX_SIZE     ; Number of each book borrowed
;     current_book_index resb 1                   ; index of current book
;     book_num resb 1                             ; Number of Book in the array / array length
    

    mov ecx, [current_book_index]
    mov edi, books_stock_borrowed
    add edi, ecx
    mov edx, [edi]
    inc edx
    mov [edi], edx

    mov edi, books_stock_available
    add edi, ecx
    mov edx, [edi]
    dec edx
    mov [edi], edx


    popa
    jmp borrow_book_menu

return_book: ; book title at edi - assume that all validation checks are done
    ; input book ID
    ; mark as returned


    pusha


    popa
    
    jmp return_book_menu

exit_program:
    ; exit cleanly

    mov eax, 1      ; syscall: exit
    xor ebx, ebx
    int 0x80
    

