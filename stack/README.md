# Стек
Библиотека со структурой данных стек
## Описание
Реализует стек, его основные основные методы и отслеживание ошибочных ситуаций.

## Перед использованием

Настройте файл settings/stack_elem_t.h:

* имя логфайла,
* тип элемента (Elem_t),
* [параметры защиты](#Ошибки)

## Использование

Включите заголовочный файл stack.h в ваш код:

```c
#include stack.h
```

 Включите Makefile в Makefile вашего проекта, содержащий переменные:

* INCLUDES_DIR - директория, где лежит эта библиотека,
* SOURCES - список исходных файлов, которые будут скомпилированы

```makefile
include $(INCLUDES_DIR)/stack/Makefile
```



## Методы:

1. Конструктор:

   ``````c
   void StackCtor(Stack *stk, size_t size, ERR_TYPE_STACK* err = NULL);
   ``````

   Конструктор разрешается использовать только для объектов, инициализированных по умолчанию, то есть:

   ```c
   Stack stack_ok  = {};
   Stack stack_err = {};
   
   stack_err.size = 300;
   
   StackCtor(&stack_ok,  19); // OK
   StackCtor(&stack_err, 19); // ERROR: стек уже был использован
   ```

   

2. Деструктор:

   ``````c
   void StacDtor(Stack *stk, ERR_TYPE_STACK* err = NULL);
   ``````

   Пример:

   ```c
   Stack stack{};
   StackCtor(&stack, 42);
   // ...
   StackDtor(&stack);
   ```

   

3. Добавить элемент (push):

   ```c
   void StackPush(Stack* stk, Elem_t elem, ERR_TYPE_STACK* err = NULL);
   ```

   Пример:

   ```c
   StackPush(&stack, 123);
   ```

   

4. Удалить элемент (pop):

   ```c
   Elem_t StackPop(Stack* stk, ERR_TYPE_STACK* err = NULL);
   ```

   Пример:

   ```c
   Elem_t elem = StackPop(&stack);
   ```

   

5. Дамп полей структуры и элементов массива стека в логфайл:

   ```c
   void StackDump(const Stack* stk);
   ```

   Дамп вызывается каждый раз, когда возникает ошибочная ситуация или когда верификатор какого-либо метода обнаружил, что стек не валиден.

   Также, дамп можно вызвать принудительно:

   ```c
   StackDump(&stack);
   ```

   Пример дампа:

   ```
   int main() at main.cpp(19):
   Stack [0x7ffeaecf2ee0] "stk" at int main() at main.cpp(10):
   {
   left struct canary:  deadca17a129dead
   right struct canary: deadca17a129dead
   struct hash value: 3153473066
   real struct hash:  3153473066
   data [0x604000000018]
   size     = 5
   capacity = 8
   	{
   	left  data canary: deadca17a129dead
   	data hash value: 1765260007
   	real data hash:  1765260007
   	* [ 1] = 0
   	* [ 2] = 1
   	* [ 3] = 2
   	* [ 4] = 3
   	* [ 5] = 4
   	  [ 6] = deadf00d
   	  [ 7] = deadf00d
   	  [ 8] = deadf00d
   	right data canary: deadca17a129dead
   	}
   }
   ```

   ## Ошибки 

   ### Различные уровни защиты стека

   * Защита ядом:

     заполняет незанятые элементы массива POISON значением.

     Для включения: в файл settings/stack_elem_t.h добавить строку:

     ```c
     #define POISON_ELEM_T_PROTECT
     ```

     а также создать константу:

     ```c
     const Elem_t POISON_ELEM_T_STACK = /* ваше значение */;
     ```

   * Канареечная защита:

     добавляет на края структуры стека и массива дополнительные поля с константными значениями. Если верификатор обнаружит, что эти поля изменились, то решит, что стек не валиден. 

     Для включения: в файл settings/stack_elem_t.h добавить строку:

     ```c
     #define CANARY_PROTECT
     ```

   * Зашита хешем:

     хеширует (в данный момент используется gnu-hash функция) поля структуры и  массив стека и сверяет его в варификаторе.

     Для включения: в файл settings/stack_elem_t.h добавить строку:

     ```c
     #define HASH_PROTECT
     ```

   * Остальные ошибки: см. в файле settings/stack_error_settings.h

   