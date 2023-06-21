const std = @import("std");

fn add(first: i64, second: i64) i64 {
    return first + second;
}

pub fn main() !void {
    std.debug.print("Input your first number\n", .{});

    const stdin = std.io.getStdIn().reader();
    var buff: [9]u8 = undefined;

    var first: i64 = @as(i64, 0);
    var second: i64 = @as(i64, 0);

    if (try stdin.readUntilDelimiterOrEof(buff[0..], '\n')) |numberInput| {
        first = try std.fmt.parseInt(i64, numberInput, 9);
    }

    std.debug.print("Input your second number\n", .{});

    if (try stdin.readUntilDelimiterOrEof(buff[0..], '\n')) |numberInput| {
        second = try std.fmt.parseInt(i64, numberInput, 9);
    }

    std.debug.print("The result is: {l}\n", .{add(first, second)});
}
