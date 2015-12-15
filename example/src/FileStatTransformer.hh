<?hh // strict

namespace hhpack\package\examples\classes;

use hhpack\package\SourceFile;
use hhpack\package\Stream;
use hhpack\package\Middleware;
use SplFileInfo;

final class FileStatTransformer implements Middleware<SourceFile, FileStatStream>
{

    public function receive(Stream<SourceFile> $stream) : FileStatStream
    {
        $factory = () ==> {
            foreach ($stream->items() as $source) {
                yield new SplFileInfo($source->getName());
            }
        };

        return FileStatStream::fromStream( $factory() );
    }

}
