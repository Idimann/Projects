type node<T> = {
    head: T,
    tail: node<T> | null
};

type tuple<T, U> = {
    first: T,
    second: U
};

const nod = <T>(f: T, s: node<T> | null): node<T> => {
    return {head: f, tail: s};
};

const tup = <T, U>(f: T, s: U): tuple<T, U> => {
    return {first: f, second: s};
};

const equals_nod = <T>(list1: node<T>, list2: node<T>): boolean => {
    if(list1.tail === null || list2.tail === null)
        return list1.head === list2.head && list1.tail === null && list2.tail === null;

    return list1.head === list2.head && equals_nod(list1.tail, list2.tail);
};

const range = (f: number, t: number): node<number> => {
    if(f >= t)
        return nod(f, null);

    return nod(f, range(f + 1, t));
};

const map = <T, U>(list: node<T>, func: (x: T) => U): node<U> => {
    if(list.tail === null)
        return nod(func(list.head), null);

    return nod(func(list.head), map(list.tail, func));
};

const combi = <T, U>(list: node<T>, list2: node<U>): node<tuple<T, U>> => {
    if(list.tail === null || list2.tail === null)
        return nod(tup(list.head, list2.head), null);

    return nod(tup(list.head, list2.head), combi(list.tail, list2.tail));
};

const combi_map = <T, U>(list: node<T>, func: (x: T) => U): node<tuple<T, U>> => {
    return combi(list, map(list, func));
};

const swap = <T>(list: node<T>): node<T> => {
    if(list.tail === null)
        return list;

    return nod(list.tail.head, nod(list.head, list.tail.tail));
}

const swap_multi = <T>(list: node<T>, func: (x: T) => number): node<T> => {
    if(list.tail === null)
        return list;

    if(func(list.head) > func(list.tail.head))
        list = swap(list);

    return nod(list.head, swap_multi(list.tail as node<T>, func));
};

const is_sorted = <T>(list: node<T>, func: (x: T) => number): boolean => {
    if(list.tail === null)
        return true;

    if(func(list.head) > func(list.tail.head))
        return false;

    return is_sorted(list.tail, func);
};

const sort = <T>(list: node<T>, func: (x: T) => number): node<T> => {
    list = swap_multi(list, func);

    if(!is_sorted(list, func))
        list = sort(list, func);

    return list;
};

const is_rising = <T, U>(list: node<tuple<T, U>>,
                         func: (x: T) => number, func2: (x: U) => number): boolean => {

    return equals_nod(sort(list, (x) => func(x.first)), sort(list, (x) => func2(x.second)));
};

const to_array = <T>(list: node<T>): T[] => {
    if(list.tail === null)
        return [list.head];

    let prev = to_array(list.tail);
    prev.unshift(list.head);
    return prev;
};

const from_array = <T>(array: T[]): node<T> => {
    if(array.length <= 1)
        return nod(array[0], null);

    return nod(array[0], from_array(array.filter((_v, i, _ar) => i > 0)));
};

const id = <T>(input: T): T => input;

const facult = (input: number): number => {
    if(input === 1)
        return 1;

    return input * facult(input - 1);
};

const arr = from_array([
    "Erik",
    "Ole"
]);

let map_arr = combi_map(arr, (x) => x.length);
map_arr = sort(map_arr, (x) => x.second);

//const rising = is_rising(map_arr, id, id);

console.log(to_array(map_arr));
