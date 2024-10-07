import cffi

ffi = cffi.FFI()

# Declare the C function signature and struct
ffi.cdef("""
typedef struct {
    char* key;
    int value;
} Item;

int binarySearch(char* keyToFind, Item* items, size_t numElements);
""")

# Load the shared library
binary_search_lib = ffi.dlopen("./lib_binary_search.so")

# Create the items array
items = ffi.new("Item[]", [
    {"key": ffi.new("char[]", b"bar"), "value": 42},
    {"key": ffi.new("char[]", b"bazz"), "value": 46},
    {"key": ffi.new("char[]", b"bob"), "value": 100},
    {"key": ffi.new("char[]", b"buzz"), "value": 46},
    {"key": ffi.new("char[]", b"foo"), "value": 10},
    {"key": ffi.new("char[]", b"jane"), "value": 200},
    {"key": ffi.new("char[]", b"x"), "value": 200}
])

# Perform the binary search
key_to_find = ffi.new("char[]", b"bob")
result = binary_search_lib.binarySearch(key_to_find, items, len(items))

if result != -1:
    print(f"Key '{ffi.string(key_to_find).decode()}' found with value: {result}")
else:
    print(f"Key '{ffi.string(key_to_find).decode()}' not found.")
