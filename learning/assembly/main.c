int foo() {
    long stackSpace[3] = {256, 0, 5};

    return sizeof(long);
}

int main() {
    return foo();
}
