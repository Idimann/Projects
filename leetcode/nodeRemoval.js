//Beats 100% lmfao
/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} n
 * @return {ListNode}
 */
var removeNthFromEnd = function(head, n) {
    const calcSize = function() {
        let c = head;
        let r;

        for(r = 1; c.next !== null; r++)
            c = c.next;

        return r;
    };

    const size = calcSize();
    let node = head;

    for(let i = 0; i < size - n - 1; i++) {
        node = node.next;
    }

    if(size <= n)
        return node.next;
    else if(node.next !== null)
        node.next = node.next.next;
    else
        return null;

    return head;
};
