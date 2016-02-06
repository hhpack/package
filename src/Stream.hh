<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package;

interface Stream<T> extends FromItems<T>
{
    public function map<Tu>((function(T):Tu) $mapper) : Stream<Tu>;
    public function concat(Stream<T> $stream) : this;
    public function reduce(T $initial, (function(T,T):T) $reducer) : T;
    public function filter((function(T):bool) $matcher) : this;
    public function skip(int $n) : Stream<T>;
    public function skipWhile((function(T):bool) $n) : Stream<T>;
    public function take(int $n) : Stream<T>;
    public function takeWhile((function(T):bool) $n) : Stream<T>;
    public function forEach((function(T):void) $callback) : void;
    public function items() : Iterable<T>;
    public function count() : int;
    public function isEmpty() : bool;
    public function firstValue() : ?T;
    public function lastValue() : ?T;
    public function pipeTo<To>(Middleware<T, To> $middleware) : To;
    public function toImmVector() : ImmVector<T>;
    public function toVector() : Vector<T>;
}
