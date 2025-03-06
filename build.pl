#!/usr/bin/perl

use warnings;
use strict;

sub usage {
    print "Usage: ./build.pl [option]\n";
    print "    test - run available tests [TODO]\n"
}

sub compile {
    print `clang emulator.c -o emulator -L./lib -I./lib -lraylib -lm`;
}

if (scalar(@ARGV) > 1) {
    print "Too many arguments\n";
    exit(1);
} elsif (scalar(@ARGV) > 0) {
    if ($ARGV[0] eq "test") {
        print "No test available yet\n";
    } else {
        print "Invalid option\n";
        usage();
        exit(1);
    }
} else {
    compile();
}
