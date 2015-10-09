<?hh //strict

/**
 * This file is part of package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace package;

interface StreamWrapper<T>
{
    public function select(Matcher<T> $matcher) : this;
    public function startsWith(string $keyword) : this;
    public function endsWith(string $keyword) : this;
    public function toImmVector() : ImmVector<T>;
    public function toVector() : Vector<T>;
    public static function fromStream(Stream<T> $classes) : this;
}
