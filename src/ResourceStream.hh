<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

final class ResourceStream<T> implements Stream<T>
{

    private ResourceIterator<T> $sources;

    public function __construct(
        Traversable<T> $sources = []
    )
    {
        $this->sources = ResourceIterator::fromItems($sources);
    }

    public function concat(Stream<T> $stream) : this
    {
        $results = $this->sources->concat( $stream->items() );
        return static::fromItems( $results );
    }

    public function reduce(T $initial, (function(T,T):T) $reducer) : T
    {
        $previous = clone $initial;

        foreach ($this->sources as $source) {
            $previous = $reducer($previous, $source);
        }
        return $previous;
    }

    public function map<Tu>((function(T):Tu) $mapper) : Stream<Tu>
    {
        $results = $this->sources->map($mapper);
        return new ResourceStream( $results );
    }

    public function filter((function(T):bool) $matcher) : this
    {
        $results = $this->sources->filter($matcher);
        return static::fromItems( $results );
    }

    public function skip(int $n) : Stream<T>
    {
        $results = $this->sources->skip($n);
        return static::fromItems( $results );
    }

    public function skipWhile((function(T):bool) $n) : Stream<T>
    {
        $results = $this->sources->skipWhile($n);
        return static::fromItems( $results );
    }

    public function take(int $n) : Stream<T>
    {
        $results = $this->sources->take($n);
        return static::fromItems( $results );
    }

    public function takeWhile((function(T):bool) $n) : Stream<T>
    {
        $results = $this->sources->takeWhile($n);
        return static::fromItems( $results );
    }

    public function forEach((function(T):void) $callback) : void
    {
        foreach ($this->sources as $source) {
            $callback($source);
        }
    }

    public function items() : Iterable<T>
    {
        return $this->toImmVector();
    }

    public function count() : int
    {
        return $this->toImmVector()->count();
    }

    public function isEmpty() : bool
    {
        return $this->toImmVector()->isEmpty();
    }

    public function firstValue() : ?T
    {
        return $this->sources->firstValue();
    }

    public function lastValue() : ?T
    {
        return $this->sources->lastValue();
    }

    public function pipeTo<To>(Middleware<T, To> $middleware) : To
    {
        return $middleware->receive($this);
    }

    public function toImmVector() : ImmVector<T>
    {
        return $this->sources->toImmVector();
    }

    public function toVector() : Vector<T>
    {
        return $this->sources->toVector();
    }

    public static function fromItems(Traversable<T> $items) : this
    {
        return new static($items);
    }

}
