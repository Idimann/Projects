//This transposes instead of doing what's it supposed to do

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} k
 * @return {ListNode}
 */
var reverseKGroup = function(head, k) {
    const swap = function(start, node, n) {
        if(n === 1)
            start.val = node.val;
        else if(node.next !== null) {
            const v = node.val;
            const re = swap(start, node.next, n - 1);
            node.next.val = v;

            return re;
        }

        return node.next;
    }

    const s = swap(head, head, k);
    if(s !== null)
        reverseKGroup(s, k);

    return head;
};
