#include "codeGenerator.h"
#include "ASTNodes.h"
#include <stdio.h>

function_t* function_head = NULL;
function_t* function_tail = NULL;

void add_function(function_definition_t* function_definition)
{
    struct function_t* function = (struct function_t*)malloc(sizeof(function_t));
    function->function_definition = function_definition;
    function->functionType = FUNCTION_DEFINITION;
    function->next = NULL;
    if (!function_head)
    {
        function_head = function;
        function_tail = function;
    }
    else {
        function_tail->next = function;
        function_tail = function;
    }
}

void add_lamda(lamda_t* lamda)
{
    struct function_t* function = (struct function_t*)malloc(sizeof(function_t));
    function->lamda = lamda;
    function->functionType = FUNCTION_LAMDA;
    function->next = NULL;
    if (!function_head)
    {
        function_head = function;
        function_tail = function;
    }
    else {
        function_tail->next = function;
        function_tail = function;
    }
}

void collect_functions_block_item(struct block_item_t* block);
void collect_function_expression(struct expression_t* expression);
void collect_function_statement(struct statement_t* statement);

void collect_function_expression(struct expression_t* expression)
{
    switch (expression->expression_type) {
        case EXPRESSION_LAMDA:
            add_lamda(expression->lamda);
            break;
        case EXPRESSION_COMPOUND:
            collect_function_expression(expression->compound_expression.left);
            collect_function_expression(expression->compound_expression.right);
        default:
    }
}

void collect_function_statement(struct statement_t* statement)
{
    switch (statement->statementType) {
        case STATEMENT_BLOCK:
            collect_functions_block_item(statement->block);
            break;
        case STATEMENT_FOR:
        // collect_function_statement(statement->for_statement.)
            break;
        case STATEMENT_IF:
            collect_function_statement(statement->if_statement->statement);
            break;
        case STATEMENT_RETURN:
            collect_function_expression(statement->return_expression);
            break;
    }
}

void collect_functions_block_item(struct block_item_t* block)
{
    if (!block) return;
    switch (block->blockItemType) 
    {
        case BLOCK_ITEM_EXPRESSION:
            collect_function_expression(block->expression);
            break;
        case BLOCK_ITEM_FUNCTION_DEFINITION:
            add_function(block->function_definition);
            collect_function_statement(block->function_definition->statement);
            break;
        case BLOCK_ITEM_TYPE_DEFINITION:
            break;
        case BLOCK_ITEM_STATEMENT:
            collect_function_statement(block->statement);
            break;
        case BLOCK_ITEM_VARIABLE_DECLARATION:
            collect_function_expression(block->variable_declaration->initializer);
            break;    
    }
    collect_functions_block_item(block->next);
}

void generate_type(FILE* file, type_t* type);
void generate_primitive(FILE* file, primitive_t primitive);
void generate_struct_member(FILE* file, struct_member_t* struct_member);
void generate_type(FILE* file, type_t* type);
void generate_statement(FILE* file, statement_t* statement);
void generate_expression(FILE* file, expression_t* expression);

void generate_primitive(FILE* file, primitive_t primitive)
{
    switch (primitive) {
        case PRIMITIVE_CHAR:
        fprintf(file, "char");
            break;
        case PRIMITIVE_SHORT:
        fprintf(file, "short");
            break;
        case PRIMITIVE_INT:
        fprintf(file, "int");
            break;
        case PRIMITIVE_LONG:
        fprintf(file, "long");
            break;
    }
}

void generate_struct_member(FILE* file, struct_member_t* struct_member)
{
    if (!struct_member) return;
    generate_type(file, struct_member->type);
    fprintf(file, " %s;", struct_member->name);
    generate_struct_member(file, struct_member->next);
}

void generate_union_member(FILE* file, union_member_t* union_member)
{
    if (!union_member) return;
    generate_type(file, union_member->type);
    fprintf(file, " %s;", union_member->name);
    generate_union_member(file, union_member->next);
}

void generate_enum_member(FILE* file, enum_member_t* enum_member)
{
    if (!enum_member) return;
    fprintf(file, "%s,", enum_member->name);
    generate_enum_member(file, enum_member->next);
}

void generate_type(FILE* file, type_t* type)
{
    if (!type) return;
    switch (type->typeType) {
        case TYPE_ENUM:
            fprintf(file, "enum {");
            generate_enum_member(file, type->enum_member);
            fprintf(file, "}");
            break;
        case TYPE_LAMDA:
            // TODO: implement typedef for lamdas
            break;
        case TYPE_IDENTIFIER:
            fprintf(file, "%s", type->identifier);
            break;
        case TYPE_PRIMITIVE:
            generate_primitive(file, type->primitive);
            break;
        case TYPE_STRUCT:
            fprintf(file, "struct {");
            generate_struct_member(file, type->struct_member);
            fprintf(file, "}");
            break;
        case TYPE_UNION:
            fprintf(file, "union {");
            generate_union_member(file, type->union_member);
            fprintf(file, "}");
            break;
    }
}

void generate_parameters(FILE* file, parameter_list_t* parameter)
{
    if (!parameter) return;
    generate_type(file, parameter->type);
    fprintf(file, " %s", parameter->name);
    if (parameter->next)
    {
        fprintf(file, ", ");
        generate_parameters(file, parameter->next);
    }
}

void generate_operator(FILE* file, operator_t op)
{
    switch (op) {
        case OPERATOR_DIVIDE:
            fprintf(file, "/");
            break;
        case OPERATOR_MINUS:
            fprintf(file, "-");
            break;
        case OPERATOR_MULTIPLY:
            fprintf(file, "*");
            break;
        case OPERATOR_PLUS:
            fprintf(file, "+");
            break;
    }
}

void generate_literal(FILE* file, literal_t* literal)
{
    if (!literal) return;
    switch (literal->literalType) {
        case LITERAL_CHAR:
            fprintf(file, "'%c'", literal->value_char);
            break;
        case LITERAL_FLOAT:
        fprintf(file, "%f", literal->value_float);
            break;
        case LITERAL_INT:
        fprintf(file, "%ld", literal->value_int);
            break;
        case LITERAL_STRING:
        fprintf(file, "\"%s\"", literal->value_string);
            break;
    }
}

void generate_args(FILE* file, argument_list_t* args)
{
    if (!args) return;
    generate_expression(file, args->expression);
    if (args->next)
    {
        fprintf(file, ", ");
        generate_args(file, args->next);
    }
}

void generate_expression(FILE* file, expression_t* expression)
{
    if (!expression) return;
    switch (expression->expression_type) {
        case EXPRESSION_ASSIGNMENT:
            fprintf(file, "%s = ", expression->assignment_expression.identifier);
            generate_expression(file, expression->assignment_expression.value);
            break;
        case EXPRESSION_IDENTIFIER:
            fprintf(file, "%s", expression->identifier);
            break;
        case EXPRESSION_LITERAL:
            generate_literal(file, expression->literal);
            break;
        case EXPRESSION_COMPOUND:
            fprintf(file, "(");
            generate_expression(file, expression->compound_expression.left);
            generate_operator(file, expression->compound_expression.op);
            generate_expression(file, expression->compound_expression.right);
            fprintf(file, ")");
            break;
        case EXPRESSION_LAMDA:
            break;
        case EXPRESSION_FUNCTION_CALL:
            fprintf(file, "%s(", expression->function_call->function_name);
            generate_args(file, expression->function_call->args);
            fprintf(file, ")");
            break;
    }
}

void generate_variable_declaration(FILE* file, variable_declaration_t* variable_declaration)
{
    if (!variable_declaration) return;
    generate_type(file, variable_declaration->type);
    fprintf(file, " %s", variable_declaration->name);
    if (variable_declaration->initializer)
    {
        fprintf(file, " = ");
        generate_expression(file, variable_declaration->initializer);
    }
}

void generate_block_item(FILE* file, block_item_t* block_item)
{
    if (!block_item) return;
    switch (block_item->blockItemType) {
        case BLOCK_ITEM_EXPRESSION:
            generate_expression(file, block_item->expression);
            fprintf(file, ";\n");
            break;
        case BLOCK_ITEM_FUNCTION_DEFINITION:
            break;
        case BLOCK_ITEM_TYPE_DEFINITION:
            break;
        case BLOCK_ITEM_STATEMENT:
            generate_statement(file, block_item->statement);
            fprintf(file, ";\n");
            break;
        case BLOCK_ITEM_VARIABLE_DECLARATION:
            generate_variable_declaration(file, block_item->variable_declaration);
            fprintf(file, ";\n");
            break;
    }
    generate_block_item(file, block_item->next);
}

void generate_statement(FILE* file, statement_t* statement)
{
    if (!statement) return;
    switch (statement->statementType) {
        case STATEMENT_BLOCK:
        fprintf(file, "{\n");
        generate_block_item(file, statement->block);
        fprintf(file, "}\n\n");
            break;
        case STATEMENT_FOR:
            break;
        case STATEMENT_IF:
            break;
        case STATEMENT_RETURN:
            break;
    }
}

void generate_functions(FILE* file, function_t* function)
{
    if (!function) return;
    switch (function->functionType) {
        case FUNCTION_DEFINITION:
            {
                function_definition_t* function_definition = function->function_definition;
                generate_type(file, function_definition->return_type);
                fprintf(file, " %s(", function_definition->function_name);
                generate_parameters(file, function_definition->parameters);
                fprintf(file, ")\n");
                generate_statement(file, function_definition->statement);
            }
            break;
        case FUNCTION_LAMDA:
            break;
    }
    generate_functions(file, function->next);
}

void generate_code(FILE* file, struct block_item_t* item)
{
    collect_functions_block_item(item);

    generate_functions(file, function_head);
}



// int var_1_1;
// int var_1_2;
// int var_1_3;
// function function_1(): int {
//     int var_2_1;
//     int var_2_2;
//     int var_2_3;
//     function function_2(): int {
//         int var_3_1;
//         int var_3_2;
//         int var_3_3;
//         function function_3(): int {

//         }
//     }
// }




// 1. Zero-Overfunction_head Memory Layouts
// (1) Enforce Structure-of-Arrays (SoA) in C Output

// Problem: C defaults to Array-of-Structs (AoS), hurting SIMD/cache.
// Solution: Transpile SoA automatically.
// Your Code
// rust

// type Point = struct { x: f32, y: f32 }  
// let points: [Point] = ...;  

// → C Output (SoA Optimized)
// c

// // Generated C (SoA layout)
// typedef struct {
//     float* x;  // Contiguous array
//     float* y;
// } Points;

// Points points = { .x = malloc(N*sizeof(float)), .y = malloc(...) };




// (2) Bitfields + Packed Structs

// Problem: C pads structs (wasting memory).
// Solution: Force bit-packing in generated C.
// Your Code
// rust

// @packed  
// type Entity = struct {  
//     active: bool,  // 1 bit  
//     type: u3,      // 3 bits  
//     id: u28,       // 28 bits  
// }  

// → C Output (Packed)
// c

// // Generated C (no padding)
// typedef struct __attribute__((packed)) {
//     uint32_t active : 1;  
//     uint32_t type : 3;  
//     uint32_t id : 28;  
// } Entity;  







// (3) Arenas as Static Pools

// Problem: C’s malloc is slow.
// Solution: Generate static arenas in C.
// Your Code
// rust

// @arena(size: 1MB)  
// type Node = struct { ... }  

// → C Output
// c

// // Generated C arena
// static uint8_t __arena_Node[1<<20];  
// static size_t __arena_Node_offset = 0;  

// Node* alloc_Node() {  
//     Node* obj = (Node*)(__arena_Node + __arena_Node_offset);  
//     __arena_Node_offset += sizeof(Node);  
//     return obj;  
// }  








// (4) Lazy Initialization

// Problem: C zero-initializes (calloc is slow).
// Solution: Generate uninitialized C code.
// Your Code
// rust

// let buffer = uninit! [u8; 1024];  

// → C Output
// c

// uint8_t buffer[1024]; // No memset  

// Why Faster?

//     Skips unnecessary writes.






// (5) Explicit SIMD Intrinsics in C

// Problem: C relies on auto-vectorization (unreliable).
// Solution: Generate architecture-specific SIMD.
// Your Code
// rust

// let sum = simd! f32x4.add(a, b);  

// → C Output (AVX-512)
// c

// #include <immintrin.h>  
// __m256 sum = _mm256_add_ps(a, b);  

// Why Faster?

//     Guaranteed vectorization.






// (6) Cache Prefetching in C

// Problem: C compilers ignore prefetch hints.
// Solution: Inject __builtin_prefetch.
// Your Code
// rust

// prefetch!(ptr, read: true);  

// → C Output
// c

// __builtin_prefetch(ptr, 0, 3); // Read, high locality  

// Why Faster?

//     Fewer cache misses.







// (7) Bounds-Check Elimination

// Problem: C has no bounds checks (unsafe).
// Solution: Add optional checks in debug mode.
// Your Code
// rust

// let x = array[i]!; // Bounds-checked  
// let y = array[i];   // Unchecked (fast)  

// → C Output
// c

// // Debug mode
// float x = (i < len) ? array[i] : abort();  

// // Release mode  
// float y = array[i];  

// Why Faster?

//     Zero-cost in release builds.




    // SoA Conversion: Transpile [Point] → struct { float* x; float* y; }.

    // Bitfields: Use __attribute__((packed)) in C.

    // Arenas: Generate static pools + bump allocators.

    // SIMD: Inject immintrin.h intrinsics.

    // Prefetching: Use __builtin_prefetch.





//     1. Custom Allocator Support

// Problem: Not all data fits arenas (e.g., long-lived objects).
// Solution: Let users plug in custom allocators (like Zig).
// Your Syntax
// rust

// @allocator(MyAllocator)  
// type LongLived = struct { ... }  

// // User-defined allocator  
// type MyAllocator = struct {  
//     fn alloc(size: usize) -> *void { ... }  
//     fn free(ptr: *void) { ... }  
// }  

// → C Output:
// c

// typedef struct {  
//     void* (*alloc)(size_t);  
//     void (*free)(void*);  
// } MyAllocator;  

// MyAllocator __alloc_LongLived = { .alloc = my_malloc, .free = my_free };  






// 2. Memory Reuse Annotations

// Problem: Temporary buffers waste allocation cycles.
// Solution: Allow object reuse to avoid reallocation.
// Your Syntax
// rust

// let buffer: [u8] @reuse = ...;  
// // Later...  
// reuse!(buffer); // Resets length, keeps capacity  

// → C Output:
// c

// uint8_t* buffer = malloc(1024);  
// size_t buffer_len = 0;  

// // Reuse:  
// buffer_len = 0; // No realloc!  

// Why?

//     Zero-cost resets for hot loops.





// 3. Memory-Mapped I/O

// Problem: Disk/GPU data requires copies.
// Solution: First-class mmap support.
// Your Syntax
// rust

// let file_data = mmap!("data.bin") as [u8]; // No copy  

// → C Output:
// c

// int fd = open("data.bin", O_RDONLY);  
// uint8_t* file_data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);  

// Why?

//     Zero-copy file/device memory access.






// 4. NUMA Awareness

// Problem: Multi-socket systems need NUMA optimizations.
// Solution: Annotate NUMA-local memory.
// Your Syntax
// rust

// @numa_node(1) // Allocate on NUMA node 1  
// type NumaData = struct { ... }  

// → C Output:
// c

// void* numa_alloc(size_t size, int node) {  
//     // Use libnuma or platform-specific APIs  
// }  

// Why?

//     ~30% speedup on multi-socket servers.