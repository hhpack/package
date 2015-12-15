<?hh // strict

namespace hhpack\package\examples\classes;

use hhpack\package\StreamSource;
use hhpack\package\SourceFile;
use hhpack\package\Matcher;
use hhpack\package\AnyMatcher;
use hhpack\package\StreamWrapper;
use hhpack\package\Middleware;
use SplFileInfo;

final class FileStatStream implements StreamWrapper<SplFileInfo>
{

    public function __construct(
        private StreamSource<SplFileInfo> $sources
    )
    {
    }

    public function select(Matcher<SplFileInfo> $matcher = new AnyMatcher()) : this
    {
        $factory = () ==> {
            foreach ($this->sources as $source) {
                if ($matcher->matches($source) === false) {
                    continue;
                }
                yield $source;
            }
        };
        return static::fromStream( $factory() );
    }

    public function items() : StreamSource<SplFileInfo>
    {
        foreach ($this->sources as $source) {
            yield $source;
        }
    }

    public function pipeTo<To>(Middleware<SplFileInfo, To> $middleware) : To
    {
        return $middleware->receive($this);
    }

    public function toImmVector() : ImmVector<SplFileInfo>
    {
        return $this->toVector()->toImmVector();
    }

    public function toVector() : Vector<SplFileInfo>
    {
        $sources = Vector {};

        foreach ($this->sources as $source) {
            $sources->add($source);
        }

        return $sources;
    }

    public static function fromStream(StreamSource<SplFileInfo> $items) : this
    {
        return new static($items);
    }

}
