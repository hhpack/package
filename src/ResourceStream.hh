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

final class ResourceStream<T> implements Stream<T>
{

    public function __construct(
        private Traversable<T> $sources = []
    )
    {
    }

    public function concat(Stream<T> $stream) : this
    {
        $factory = () ==> {
            foreach ($stream->items() as $item) {
                yield $item;
            }

            foreach ($this->items() as $item) {
                yield $item;
            }
        };
        return static::fromItems( $factory() );
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
        $factory = () ==> {
            foreach ($this->sources as $source) {
                yield $mapper($source);
            }
        };
        return new ResourceStream( $factory() );
    }

    public function filter((function(T):bool) $matcher) : this
    {
        $factory = () ==> {
            foreach ($this->sources as $source) {
                if ($matcher($source) === false) {
                    continue;
                }
                yield $source;
            }
        };
        return static::fromItems( $factory() );
    }

    public function forEach((function(T):void) $callback) : void
    {
        foreach ($this->sources as $source) {
            $callback($source);
        }
    }

    public function items() : Iterator<T>
    {
        foreach ($this->sources as $source) {
            yield $source;
        }
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
        return ImmVector::fromItems($this->sources)->firstValue();
    }

    public function lastValue() : ?T
    {
        return ImmVector::fromItems($this->sources)->lastValue();
    }

    public function pipeTo<To>(Middleware<T, To> $middleware) : To
    {
        return $middleware->receive($this);
    }

    public function toImmVector() : ImmVector<T>
    {
        return ImmVector::fromItems($this->sources);
    }

    public function toVector() : Vector<T>
    {
        return Vector::fromItems($this->sources);
    }

    public static function fromItems(Traversable<T> $items) : this
    {
        return new static($items);
    }

}
