<?hh // strict

namespace hhpack\package\examples\classes;

use hhpack\package\SourceFile;
use hhpack\package\Stream;
use hhpack\package\StreamObject;
use hhpack\package\Middleware;
use SplFileInfo;

final class FileStatTransformer implements Middleware<SourceFile, StreamObject<SplFileInfo>>
{

    public function receive(Stream<SourceFile> $stream) : StreamObject<SplFileInfo>
    {
        $factory = () ==> {
            foreach ($stream->items() as $source) {
                yield new SplFileInfo($source->getName());
            }
        };

        return StreamObject::fromStream( $factory() );
    }

}
