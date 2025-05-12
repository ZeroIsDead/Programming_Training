%define BOOK_MAX_SIZE 5
%define BOOK_SIZE 20

section .data                   ; Data segment (initialized data)
    colon_separator db ':'

    clear_screen_sequence db 0x1b, "[H", 0x1b, "[J"
    clear_screen_len equ $ - clear_screen_sequence

    file db "books.txt", 0      ; Null-terminated for file operations
    file_name_len equ $ - file - 1

    menu_choices    db "===== Library Management System =====", 10
                    db "1. List Books", 10
                    db "2. Add Book", 10
                    db "3. Restock Book", 10
                    db "4. Borrow Book", 10
                    db "5. Return Book", 10
                    db "6. Exit Program", 10
    menu_len equ $ - menu_choices

    query_user db "Enter an Input: "
    qu_len equ $ - query_user

    invalid_msg db "Invalid Input!", 10
    invalid_msg_len equ $ - invalid_msg

    list_book_menu_text db "These are the Books Recorded in the System: ", 10
    list_book_menu_text_len equ $ - list_book_menu_text
    
    no_books_text db "There are no Books Recorded in the System!", 10
    no_books_text_len equ $ - no_books_text

    add_book_query db "Enter the Book Title You Want to Add: "
    add_book_query_len equ $ - add_book_query

    invalid_add_book_query db "The Book already Exists!", 10
    invalid_add_book_query_len equ $ - invalid_add_book_query
    
    book_added_msg db "Book added successfully!", 10
    book_added_msg_len equ $ - book_added_msg

    book_limit_msg db "Book limit reached! Maximum 5 books allowed.", 10
    book_limit_msg_len equ $ - book_limit_msg

    restock_book_menu_text db "These are the books available to be restocked: ", 10
    restock_book_menu_text_len equ $ - restock_book_menu_text
    
    restock_book_query_title db "Enter the Book Title You Want to Restock: "
    restock_book_query_title_len equ $ - restock_book_query_title

    restock_book_query_quant db "Enter the quantity: "
    restock_book_query_quant_len equ $ - restock_book_query_quant

    book_restocked_msg db "Book restocked Successfully!", 10
    book_restocked_msg_len equ $ - book_restocked_msg

    invalid_restock_book_query db "The Book is not present or Invalid Quantity Entered!", 10
    invalid_restock_book_query_len equ $ - invalid_restock_book_query

    borrow_book_query db "Enter the Book Title You Want to Borrow: "
    borrow_book_query_len equ $ - borrow_book_query

    borrow_book_menu_text db "These are the Books Available to Borrow:", 10
    borrow_book_menu_text_len equ $ - borrow_book_menu_text

    invalid_borrow_book_query db "The Book is not present or no copies available!", 10
    invalid_borrow_book_query_len equ $ - invalid_borrow_book_query

    book_borrowed_msg db "Book borrowed successfully!", 10
    book_borrowed_msg_len equ $ - book_borrowed_msg

    return_book_menu_text db "These are the Books that haven't Been Returned:", 10
    return_book_menu_len equ $ - return_book_menu_text

    return_book_query db "Enter the Book Title You Want to Return: "
    return_book_query_len equ $ - return_book_query

    invalid_return_book_query db "The Book is Not Recorded as Borrowed!", 10
    invalid_return_book_query_len equ $ - invalid_return_book_query

    book_returned_msg db "Book returned successfully!", 10
    book_returned_msg_len equ $ - book_returned_msg

    no_borrowed_books_msg db "No books have been borrowed.", 10
    no_borrowed_books_msg_len equ $ - no_borrowed_books_msg

    return_to_menu_query db "Return to Menu (Y|N): "
    return_to_menu_query_len equ $ - return_to_menu_query

    newline db 10
    book_entry_format db "%d. %s (%d available)", 10, 0

section .bss                        ; BSS segment (uninitialized data)
    buffer resb 100                             ; output buffer
    current_book_title resb 20                  ; Holds the Title of the current book
    books resb 100                              ; 5 x 20 bytes (Each book 20 bytes) 
    books_stock_available resb BOOK_MAX_SIZE    ; Number of each book available in the system
    books_stock_borrowed resb BOOK_MAX_SIZE     ; Number of each book borrowed
    current_book_index resb 1                   ; index of current book
    book_num resb 1                             ; Number of Book in the array / array length
    inputBuffer resb 100                        ; buffer for user input - Reads all 100 bytes regardless
    input resb 100                              ; current user input - assume a line is one input - stores one line/current user input
    fileBuffer resb 100                         ; buffer for file io
    fd_in resd 1                               ; File descriptor for reading
    fd_out resd 1                               ; File descriptor for writing

section .text               ; Code segment
    global _start           ; Entry point for linker (Linux) or main (Windows)

print_string: ; assumes string address and length in ecx and edx respectively
    pusha                   ; push all registers onto stack

    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    int 0x80

    popa
    ret

%macro PRINT_STR 2      ; takes 2 parameters: string label, length
    pusha                ; push all registers onto stack
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
    ; Initialize book array from file at startup
    call initialize_book_array
    call main_menu
    jmp exit_program

get_len:  ; String stored in edi, returns len at edx
    push ecx
    push edi
    xor ecx, ecx ; reset to 0

    .len_loop:
        cmp byte [edi], 10              ; newline?
        je .done_len
        cmp byte [edi], 0               ; Terminating character?
        je .done_len

        inc edi
        inc ecx
        cmp ecx, 100                    ; max 100 char
        jne .len_loop

    .done_len:
        mov edx, ecx
        pop edi
        pop ecx
        ret


strip_prefix_and_suffix_whitespaces: ; assumes string address at edi and that only one line of string, so before any newline
    push esi
    push eax
    push ecx
    mov esi, edi

    xor ecx, ecx

    ; Find the end of the string and replace newline with null
    .find_start:
        mov al, byte [esi]
        
        cmp al, 32          ; Whitespace
        jne .copy_loop_init
        cmp ecx, 100        ; if length more than buffer size
        je .copy_loop_init

        inc esi             ; increment string address
        inc ecx             ; increment index register
        jmp .find_start


    .copy_loop_init:
        xor ecx, ecx
        
    .copy_loop:
        mov byte [edi + ecx], al ; copy non-whitespace character to input

        ; increment the position / index register
        inc ecx

        mov al, byte [esi + ecx] ; move new char from input Buffer to register

        cmp al, 10
        je .end_found 
        cmp al, 0
        je .end_found
        cmp al, 13
        je .end_found
        cmp ecx, 100
        je .end_found


        jmp .copy_loop
        
    .end_found:
        mov byte [edi + ecx], 0 ; change last character to terminating char

        pop ecx
        pop eax
        pop esi

        ret
read_file: ; open and read book txt
    ; Open file for reading (O_RDONLY)
    mov eax, 5          ; sys_open
    mov ebx, file       ; filename
    mov ecx, 0          ; O_RDONLY
    mov edx, 0664o      ; mode (read/write permissions)
    int 0x80
    
    ; Check for errors
    cmp eax, 0
    jl .file_error      ; If eax < 0, there was an error
    
    ; Store file descriptor properly as a dword
    mov dword [fd_in], eax
    
    ; Clear fileBuffer before reading
    push ecx
    push eax
    xor eax, eax        ; Value to store (0)
    mov ecx, 100
    mov edi, fileBuffer
    rep stosb           ; Store byte in AL at ES:EDI, increment EDI
    pop eax
    pop ecx
    
    ; Read file content
    mov eax, 3          ; sys_read
    mov ebx, dword [fd_in]    ; file descriptor
    mov ecx, fileBuffer ; buffer
    mov edx, 100        ; buffer size
    int 0x80
    
    ; Check read result
    cmp eax, 0
    jl .read_error      ; Error occurred
    
    ; Make sure the buffer is null-terminated
    mov byte [fileBuffer + eax], 0
    
    ; Close the file
    push eax            ; Save number of bytes read
    mov eax, 6          ; sys_close
    mov ebx, dword [fd_in]
    int 0x80
    pop eax             ; Restore number of bytes read
    
    ret
    
    .read_error:
        ; Handle read error
        mov eax, 6      ; sys_close
        mov ebx, dword [fd_in]
        int 0x80
        ; Fall through to file_error
    
    .file_error:
        ; Initialize empty state if file doesn't exist
        mov byte [book_num], 0
        ; Ensure fileBuffer is empty
        mov byte [fileBuffer], 0
        ret

write_file: ; Save books back to file
    ; Open file for writing (O_WRONLY | O_CREAT | O_TRUNC)
    mov eax, 5          ; sys_open
    mov ebx, file       ; filename
    mov ecx, 0x241      ; O_WRONLY | O_CREAT | O_TRUNC (0x01 | 0x40 | 0x200)
    mov edx, 0664o      ; mode (read/write permissions)
    int 0x80
    
    ; Check for errors
    cmp eax, 0
    jl .write_error
    
    ; Store file descriptor properly
    mov dword [fd_out], eax
    
    ; Prepare to write each book
    xor ecx, ecx        ; Book index counter

    .write_loop:
        cmp cl, byte [book_num]
        jge .done_writing
        
        ; Get book at index
        push ecx
        
        ; Clear the buffer first
        push ecx
        push eax
        xor eax, eax
        mov ecx, 100
        mov edi, fileBuffer
        rep stosb        ; Clear buffer
        pop eax
        pop ecx
        
        call get_book_at_index  ; Sets edi to point to current book

        ; Calculate string length
        call get_len            ; Returns length in edx

        ; Make sure length is valid
        cmp edx, 0
        jle .next_book
        cmp edi, 0
        jle .next_book
        cmp byte [edi], 0
        jle .next_book

        ; Write book title to file
        mov eax, 4              ; sys_write
        mov ebx, dword [fd_out] ; file descriptor
        mov ecx, edi            ; buffer (book string)
        ; edx already has length
        int 0x80

        ; Check write result
        cmp eax, 0
        jl .write_error_close
        
        ; Write stock and borrowed information - convert to a simple format
        ; Format: "title:stock:borrowed\n"
        
        ; Now write the colon separator
        mov eax, 4
        mov ebx, dword [fd_out]
        mov ecx, colon_separator ; we need to add this to .data
        mov edx, 1
        int 0x80
        
        ; Write available stock (convert to ASCII)
        pop ecx              ; Get book index back
        push ecx             ; And save it again
        
        ; Convert stock to ASCII and write
        mov al, byte [books_stock_available + ecx]
        add al, '0'          ; Convert number to ASCII
        mov byte [fileBuffer], al
        
        mov eax, 4
        mov ebx, dword [fd_out]
        mov ecx, fileBuffer
        mov edx, 1
        int 0x80
        
        ; Write another colon separator
        mov eax, 4
        mov ebx, dword [fd_out]
        mov ecx, colon_separator
        mov edx, 1
        int 0x80
        
        ; Write borrowed amount (convert to ASCII)
        pop ecx              ; Get book index back
        push ecx             ; And save it again
        
        ; Convert borrowed to ASCII and write
        mov al, byte [books_stock_borrowed + ecx]
        add al, '0'          ; Convert number to ASCII
        mov byte [fileBuffer], al
        
        mov eax, 4
        mov ebx, dword [fd_out]
        mov ecx, fileBuffer
        mov edx, 1
        int 0x80
        
        ; Write newline
        mov eax, 4
        mov ebx, dword [fd_out]
        mov ecx, newline
        mov edx, 1
        int 0x80
        
    .next_book:
        ; Next book
        pop ecx
        inc ecx
        jmp .write_loop
        
    .done_writing:
        ; Close the file
        mov eax, 6          ; sys_close
        mov ebx, dword [fd_out]
        int 0x80
        ret
        
    .write_error_close:
        ; Close file before returning error
        pop ecx              ; Clean the stack
        mov eax, 6
        mov ebx, dword [fd_out]
        int 0x80
        ; Fall through to write_error
        
    .write_error:
        ; Handle write error
        ret

initialize_book_array: ; read from text file and places saved books into array
    pusha
        
    call read_file  ; Read file content into fileBuffer
    
    ; If fileBuffer is empty, we're done (empty file or file doesn't exist)
    cmp byte [fileBuffer], 0
    je .done_parsing
    
    ; Parse file content and populate books array
    xor ecx, ecx    ; Book counter
    mov esi, fileBuffer
        
    .parse_loop:
        ; Check if we've reached the end of input or book limit
        cmp byte [esi], 0
        je .done_parsing
        cmp cl, BOOK_MAX_SIZE
        jge .done_parsing
        
        ; Save book counter
        push ecx
        
        ; Calculate destination in books array
        movzx ecx, byte [book_num]
        imul ecx, BOOK_SIZE    ; ecx = book_num * BOOK_SIZE
        lea edi, [books + ecx] ; edi points to book slot
        
        ; Parse line format: "title:stock:borrowed"
        ; First read the title until we hit a colon
        mov edx, 0  ; Character counter
        
        .parse_title_loop:
            mov al, byte [esi]
            
            ; Check for end of line, string, or field separator
            cmp al, 0
            je .done_parsing
            cmp al, 10
            je .end_line
            cmp al, 13
            je .end_line
            cmp al, ':'
            je .parse_stock
            
            ; Copy character to book title
            mov byte [edi + edx], al
            inc esi
            inc edx
            
            ; Check if we've reached max title length
            cmp edx, BOOK_SIZE - 1
            jl .parse_title_loop
            
            ; Title too long, skip to next field
            .find_colon:
                mov al, byte [esi]
                inc esi
                
                cmp al, 0
                je .done_parsing
                cmp al, 10
                je .end_line
                cmp al, 13
                je .end_line
                cmp al, ':'
                je .parse_stock
                
                jmp .find_colon
        
        .parse_stock:
            ; Null-terminate the title
            mov byte [edi + edx], 0
            
            ; Move past colon
            inc esi
            
            ; Read stock value (single digit)
            mov al, byte [esi]
            sub al, '0'       ; Convert ASCII to number
            
            ; Store in books_stock_available
            mov byte [books_stock_available + ecx], al
            
            ; Move past stock value to next colon
            inc esi
            
            ; Check if we have a colon next
            cmp byte [esi], ':'
            jne .end_line
            
            ; Move past colon
            inc esi
            
            ; Read borrowed value (single digit)
            mov al, byte [esi]
            sub al, '0'      ; Convert ASCII to number
            
            ; Store in books_stock_borrowed
            mov byte [books_stock_borrowed + ecx], al
            
            ; Move past borrowed value
            inc esi
            
        .end_line:
            ; Skip to next line
            .find_newline:
                mov al, byte [esi]
                
                cmp al, 0
                je .add_book
                cmp al, 10
                je .next_line_found
                
                inc esi
                jmp .find_newline
                
        .next_line_found:
            ; Move past newline
            inc esi
            
        .add_book:
            ; Increment book count
            inc byte [book_num]
            
            ; Restore book counter
            pop ecx
            inc ecx
            jmp .parse_loop
                
    .done_parsing:
        popa
        ret
clear_input_var: ; cleans input var
    push ecx
    push edi
    push eax

    ; write 0 to edi 100 times
    mov ecx, 100
    mov edi, input
    xor eax, eax
    rep stosb  

    pop eax
    pop edi
    pop ecx
    ret
shift_inputBuffer: ; esi - string address, ecx - shift offset
    push ecx
    push esi
    push edi
    push eax

    mov edi, inputBuffer
    mov esi, inputBuffer
    add esi, ecx

    mov eax, 100
    sub eax, ecx

    .shift_loop:
        mov al, byte [esi]
        mov byte [edi], al
        inc esi
        inc edi
        inc ecx
        
        cmp ecx, 100
        je .shift_loop_2

        jmp .shift_loop

    .shift_loop_2:
        cmp eax, 0
        je .shift_done

        mov byte [edi], 0
        inc edi
        dec eax

        jmp .shift_loop_2

    .shift_done:
        pop eax
        pop edi
        pop esi
        pop ecx
        ret
get_input_from_buffer: ; assume string is stored in edi, place line into input var
    push eax
    push ecx

    xor ecx, ecx

    call clear_input_var

    .copy_from_buffer:
        mov al, byte [inputBuffer + ecx]
        mov byte [input + ecx], al
        inc ecx

        cmp al, 10      ; if newline
        je .get_input_from_buffer_finish
        cmp al, 0       ; if terminal char
        je .get_input_from_buffer_finish
        cmp al, 13      ; if carriage return
        je .get_input_from_buffer_finish
        cmp ecx, 100    ; if more than buffer length
        je .get_input_from_buffer_finish

        jmp .copy_from_buffer


    .get_input_from_buffer_finish:
        mov byte [input + ecx], 0       ; terminate string
        call shift_inputBuffer          ; shift offset at ecx
        pop ecx
        pop eax
        ret
check_buffer_has_content: ; returns code in al register (1 - has, 0 - no content)
    mov al, byte [inputBuffer]
    cmp al, 0
    je .doesnt_have_content
    cmp al, 10
    je .doesnt_have_content
    cmp al, 13
    je .doesnt_have_content

    .has_content:
        xor eax, eax
        mov al, 1   ; code 1 - has content
        ret

    .doesnt_have_content:
        xor eax, eax
        mov al, 0   ; code 0 - no content
        ret

read_line: ; read the entire stdin (100 bytes) - store in input
    pusha

    ; if input Buffer still have content then get current Input
    .check_buffer_content:
        call check_buffer_has_content 
        cmp al, 1
        je .get_current_input ; if has content, do not call read but take next line from inputBuffer

    .clear_and_read:
        mov eax, 3              ; syscall: read
        mov ebx, 0              ; stdin
        mov ecx, inputBuffer    ; buffer to store input
        mov edx, 100            ; number of bytes to read
        int 0x80                 ; input stored in inputBuffer

    .get_current_input:
        call get_input_from_buffer ; get input string from inputBuffer and move to input memory
        
        ; trim / clean the input
        mov edi, input

        call strip_prefix_and_suffix_whitespaces

    .validation:             ; if the content of the input is garbage, then read again
        cmp byte [edi], 10   ; if new line
        je .check_buffer_content
        cmp byte [edi], 0    ; if terminal char
        je .check_buffer_content
        cmp byte [edi], 13    ; if carriage return char
        je .check_buffer_content

    popa
    ret

get_user_input: ; prints query (expected at ecx) and length at (edx) and read the line - store in input
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
    call clear_screen
    call print_menu
    
    ASK_AND_READ query_user, qu_len

    ; If Match then Jump
    mov al, byte [input]
    JMP_TO_SUB_MENU_ON_COND '1', .list_book_section
    JMP_TO_SUB_MENU_ON_COND '2', .add_book_section
    JMP_TO_SUB_MENU_ON_COND '3', .restock_book_section
    JMP_TO_SUB_MENU_ON_COND '4', .borrow_book_section
    JMP_TO_SUB_MENU_ON_COND '5', .return_book_section
    JMP_TO_SUB_MENU_ON_COND '6', .exit_program_section

    ; No match then Invalid and Print Again
    PRINT_STR invalid_msg, invalid_msg_len 
    jmp main_menu

    .list_book_section:
        call list_book_menu
        jmp main_menu

    .add_book_section:
        call add_book_menu
        jmp main_menu

    .restock_book_section:
        call restock_book_menu
        jmp main_menu

    .borrow_book_section:
        call borrow_book_menu
        jmp main_menu

    .return_book_section:
        call return_book_menu
        jmp main_menu

    .exit_program_section:
        jmp exit_program

clear_screen:
    PRINT_STR clear_screen_sequence, clear_screen_len
    ret

print_menu:
    PRINT_STR menu_choices, menu_len
    ret

print_available_books:
    pusha
    
    ; Check if any books exist
    cmp byte [book_num], 0
    je .no_books
    
    xor ecx, ecx    ; Book index counter
    
    .print_loop:
        cmp cl, byte [book_num]
        jge .done_printing
        
        ; Print book number
        mov al, cl
        add al, '1'    ; Convert to ASCII
        mov byte [buffer], al
        mov byte [buffer + 1], '.'
        mov byte [buffer + 2], ' '
        
        PRINT_STR buffer, 3
        
        ; Print book title
        push ecx
        call get_book_at_index    ; Sets edi to current book
        
        ; Calculate string length
        call get_len              ; Returns length in edx
        
        PRINT_STR edi, edx
        
        ; Print available count
        mov al, ' '
        mov byte [buffer], al
        mov byte [buffer + 1], '('
        
        mov al, byte [books_stock_available + ecx]
        add al, '0'    ; Convert to ASCII
        mov byte [buffer + 2], al
        
        mov byte [buffer + 3], ' '
        mov byte [buffer + 4], 'a'
        mov byte [buffer + 5], 'v'
        mov byte [buffer + 6], 'a'
        mov byte [buffer + 7], 'i'
        mov byte [buffer + 8], 'l'
        mov byte [buffer + 9], 'a'
        mov byte [buffer + 10], 'b'
        mov byte [buffer + 11], 'l'
        mov byte [buffer + 12], 'e'
        mov byte [buffer + 13], ')'
        mov byte [buffer + 14], 10    ; Newline
        
        PRINT_STR buffer, 15
        
        pop ecx
        inc ecx
        jmp .print_loop
        
    .no_books:
        PRINT_STR no_books_text, no_books_text_len
        
    .done_printing:
        popa
        ret

print_borrowed_books:
    pusha
    
    ; Check if any books are borrowed
    xor ecx, ecx
    xor edx, edx    ; Borrowed books counter
    
    .check_borrowed:
        cmp cl, byte [book_num]
        jge .check_done
        
        cmp byte [books_stock_borrowed + ecx], 0
        je .next_book
        
        ; Found a borrowed book
        inc edx
        
    .next_book:
        inc ecx
        jmp .check_borrowed
        
    .check_done:
        ; If no books borrowed, print message
        cmp edx, 0
        jz .no_borrowed
        
        ; Print borrowed books
        xor ecx, ecx
        
    .print_loop:
        cmp cl, byte [book_num]
        jge .done_printing
        
        ; Check if this book is borrowed
        cmp byte [books_stock_borrowed + ecx], 0
        je .skip_book
        
        ; Print book number
        mov al, cl
        add al, '1'    ; Convert to ASCII
        mov byte [buffer], al
        mov byte [buffer + 1], '.'
        mov byte [buffer + 2], ' '
        
        PRINT_STR buffer, 3
        
        ; Print book title
        push ecx
        call get_book_at_index    ; Sets edi to current book
        
        ; Calculate string length
        call get_len              ; Returns length in edx
        
        PRINT_STR edi, edx
        
        ; Print borrowed count
        mov al, ' '
        mov byte [buffer], al
        mov byte [buffer + 1], '('
        
        movzx eax, byte [books_stock_borrowed + ecx]
        add al, '0'    ; Convert to ASCII
        mov byte [buffer + 2], al
        
        mov byte [buffer + 3], ' '
        mov byte [buffer + 4], 'b'
        mov byte [buffer + 5], 'o'
        mov byte [buffer + 6], 'r'
        mov byte [buffer + 7], 'r'
        mov byte [buffer + 8], 'o'
        mov byte [buffer + 9], 'w'
        mov byte [buffer + 10], 'e'
        mov byte [buffer + 11], 'd'
        mov byte [buffer + 12], ')'
        mov byte [buffer + 13], 10    ; Newline
        
        PRINT_STR buffer, 14
        
        pop ecx
        
    .skip_book:
        inc ecx
        jmp .print_loop
        
    .no_borrowed:
        PRINT_STR no_borrowed_books_msg, no_borrowed_books_msg_len
        
    .done_printing:
        popa
        ret
list_book_menu:
    ; Display borrowed books
    PRINT_STR list_book_menu_text, list_book_menu_text_len
    call print_available_books
    
    ; Simple prompt to return
    ASK_AND_READ return_to_menu_query, return_to_menu_query_len
    
    cmp byte [input], 'N' ; if dont want to return then loop
    je list_book_menu
    cmp byte [input], 'n' ; if dont want to return then loop
    je list_book_menu
    
    ret
add_book_menu:
    ; Check if book limit reached
    cmp byte [book_num], BOOK_MAX_SIZE
    jge .book_limit_reached

    ; Print prompt for book title
    ASK_AND_READ add_book_query, add_book_query_len
    
    ; Handle the input - copy from inputBuffer to input
    ; Replace newline with null terminator
    mov edi, input
    xor ecx, ecx

    call get_len ; expects string at edi, returns edx

    ; Jump to Invalid Book if Length of Title >= 20
    cmp edx, 20      
    jge .invalid_book

    call book_exist  ; Returns index in al, 5 if not found
    
    cmp al, byte [book_num]
    jl .invalid_book    ; Book already exists
    
    ; Book doesn't exist, add it
    movzx ecx, byte [book_num]      ; Get current book count
    
    call get_book_at_index          ; get starting index address in array in edi
    
    ; Copy title from input to books array
    xor ecx, ecx
    mov esi, input
    
    .copy_title_loop:
        mov al, byte [esi + ecx]
        mov byte [edi + ecx], al
        inc ecx
        
        cmp al, 0
        jz .title_copied
        cmp ecx, 19
        jl .copy_title_loop
        
        
    .title_copied:
        mov byte [edi + ecx], 0  ; Ensure null termination
        ; Set initial available count
        movzx ecx, byte [book_num]
        mov byte [books_stock_available + ecx], 1
        mov byte [books_stock_borrowed + ecx], 0
        
        ; Increment book count
        inc byte [book_num]
        
        ; Save changes to file
        call write_file
        
        ; Show success message
        PRINT_STR book_added_msg, book_added_msg_len
        jmp .done
        
    .invalid_book:
        PRINT_STR invalid_add_book_query, invalid_add_book_query_len
        jmp .done
        
    .book_limit_reached:
        PRINT_STR book_limit_msg, book_limit_msg_len
        
    .done:
        ASK_AND_READ return_to_menu_query, return_to_menu_query_len

        cmp byte [input], 'N' ; if dont want to return then loop
        je add_book_menu
        cmp byte [input], 'n' ; if dont want to return then loop
        je add_book_menu

        ret

restock_book_menu:
    cmp byte [book_num], 0
    je .no_books

    ; Display available books
    PRINT_STR restock_book_menu_text, restock_book_menu_text_len
    call print_available_books
    
    ; Ask which book to borrow
    ASK_AND_READ restock_book_query_title, restock_book_query_title_len
    
    ; Copy input to esi for book_exist
    mov esi, input
    
    ; Check if book exists
    call book_exist  ; Returns index in al
    
    cmp al, byte [book_num]
    jge .book_not_found
    
    ; Book found, store index in ecx for borrow_book
    movzx ecx, al

    .book_quant_loop:
        ASK_AND_READ restock_book_query_quant, restock_book_query_quant_len

        mov al, byte [input] ; 1 byte quantity

        cmp al, 0
        je .book_quant_loop

    ; Book is available, restock it
    call restock_book

    ; Show success message
    PRINT_STR book_restocked_msg_len, book_restocked_msg_len
    jmp .done
        
    .book_not_found:
        PRINT_STR invalid_restock_book_query, invalid_restock_book_query_len
        jmp .done

    .no_books:
        PRINT_STR no_books_text, no_books_text_len
    
    .done:
        ; Simple prompt to return
        ASK_AND_READ return_to_menu_query, return_to_menu_query_len

        cmp byte [input], 'N' ; if dont want to return then loop
        je restock_book_menu
        cmp byte [input], 'n' ; if dont want to return then loop
        je restock_book_menu
        
        ret
borrow_book_menu:
    cmp byte [book_num], 0
    je .no_books

    ; Display available books
    PRINT_STR borrow_book_menu_text, borrow_book_menu_text_len
    call print_available_books
    
    ; Ask which book to borrow
    ASK_AND_READ borrow_book_query, borrow_book_query_len
    
    ; Copy input to esi for book_exist
    mov esi, input
    
    ; Check if book exists
    call book_exist  ; Returns index in al
    
    cmp al, byte [book_num]
    jge .book_not_found
    
    ; Book found, store index in ecx for borrow_book
    movzx ecx, al

    ; Check if book has available copies
    cmp byte [books_stock_available + ecx], 0
    je .no_copies_available

    ; Book is available, borrow it
    call borrow_book
    
    ; Show success message
    PRINT_STR book_borrowed_msg, book_borrowed_msg_len
    jmp .done
        
    .book_not_found:
    .no_copies_available:
        PRINT_STR invalid_borrow_book_query, invalid_borrow_book_query_len
        jmp .done
    
    .no_books:
        PRINT_STR no_books_text, no_books_text_len

    .done:
        ; Simple prompt to return
        ASK_AND_READ return_to_menu_query, return_to_menu_query_len

        cmp byte [input], 'N' ; if dont want to return then loop
        je borrow_book_menu
        cmp byte [input], 'n' ; if dont want to return then loop
        je borrow_book_menu
        
        ret

return_book_menu:
    pusha

    xor edx, edx    ; Borrowed books counter
    
    .check_borrowed:
        cmp cl, byte [book_num]
        jge .check_done
        
        cmp byte [books_stock_borrowed + ecx], 0
        je .next_book
        
        ; Found a borrowed book
        inc edx
        
    .next_book:
        inc ecx
        jmp .check_borrowed
        
    .check_done:
        ; If no books borrowed, print message
        cmp edx, 0
        je .no_borrowed
        
        ; Print borrowed books
        xor ecx, ecx

    ; Display borrowed books
    PRINT_STR return_book_menu_text, return_book_menu_len
    call print_borrowed_books
    
    ; Ask which book to return
    ASK_AND_READ return_book_query, return_book_query_len
    
    
    ; Copy input to esi for book_exist
    mov esi, input
    
    ; Check if book exists
    call book_exist  ; Returns index in al, 5 if not found
    
    cmp al, byte [book_num]
    jge .book_not_found
    
    ; Book found, store index in ecx for return_book
    movzx ecx, al
    
    ; Check if book has borrowed copies
    cmp byte [books_stock_borrowed + ecx], 0
    je .not_borrowed
    
    ; Book is borrowed, return it
    call return_book
    
    ; Show success message
    PRINT_STR book_returned_msg, book_returned_msg_len
    jmp .done
        
    .book_not_found:
    .not_borrowed:
        PRINT_STR invalid_return_book_query, invalid_return_book_query_len
        jmp .done

    .no_borrowed:
        PRINT_STR no_borrowed_books_msg, no_borrowed_books_msg_len

    .done:
        ; Simple prompt to return
        ASK_AND_READ return_to_menu_query, return_to_menu_query_len
        
        cmp byte [input], 'N' ; if dont want to return then loop
        je return_book_menu
        cmp byte [input], 'n' ; if dont want to return then loop
        je return_book_menu
        
        popa
        ret

compare_string: ; stringA - edi, stringB - esi, size - ecx, returns bool at dl 
    push ecx
    push eax
    xor edx, edx    ; Clear result register
    
    .compare_loop:
        cmp esi, 0
        je .not_equal

        mov al, byte [edi]
        cmp al, byte [esi]
        jne .not_equal
        
        ; Check for end of string
        cmp al, 0
        jz .equal
        cmp al, 10
        je .equal

        ; Continue comparing
        inc edi
        inc esi
        dec ecx
        cmp ecx, 0
        jz .equal
        
        jmp .compare_loop
        
    .equal:
        mov dl, 1    ; Strings are equal
        jmp .done
        
    .not_equal:
        mov dl, 0    ; Strings are not equal
        
    .done:
        pop eax
        pop ecx
        ret

get_book_at_index: ; index at ecx and returns address of book in edi
    push eax
    
    imul eax, ecx, BOOK_SIZE       ; calculate offset
    lea edi, [books + eax]              ; move to correct Book
    
    pop eax
    ret

book_exist: ; book title at esi - returns index at al register
    push ecx
    push edx
    
    xor ecx, ecx    ; book index
    
    .check_loop:
        cmp cl, byte [book_num]
        jge .book_not_found

        ; Get book at current index
        push ecx
        call get_book_at_index    ; Sets edi to current book
        pop ecx
        
        ; Compare book titles
        push ecx
        push esi
        push edi
        
        mov ecx, BOOK_SIZE
        call compare_string    ; Returns result in dl
        
        pop edi
        pop esi
        pop ecx
        
        ; Check result
        cmp dl, 1
        je .book_found
        
        ; Move to next book
        inc ecx
        jmp .check_loop
        
    .book_found:
        mov al, cl    ; Return book index
        jmp .done
        
    .book_not_found:
        mov al, byte [book_num]     ; Return 5 (invalid index) if not found
        
    .done:
        pop edx
        pop ecx
        ret

restock_book: ; index at ecx, quant at al
    sub al, '0' ; turn ascii into int
    mov byte [books_stock_available + ecx], al

    call write_file
    ret

borrow_book: ; index at ecx
    ; Decrement available count
    dec byte [books_stock_available + ecx]
    
    ; Increment borrowed count
    inc byte [books_stock_borrowed + ecx]
    
    ; Save changes to file
    call write_file
    ret

return_book: ; index at ecx
    ; Increment available count
    inc byte [books_stock_available + ecx]
    
    ; Decrement borrowed count
    dec byte [books_stock_borrowed + ecx]
    
    ; Save changes to file
    call write_file
    ret

exit_program:
    ; Save changes to file before exiting
    call write_file
    
    ; Exit cleanly
    mov eax, 1      ; syscall: exit
    xor ebx, ebx    ; return code 0
    int 0x80