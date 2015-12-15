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
    public function select(Matcher<T> $matcher) : this;
    public function items() : StreamSource<T>;
    public function pipeTo<To>(Middleware<T, To> $middleware) : To;
    public function toImmVector() : ImmVector<T>;
    public function toVector() : Vector<T>;
}
