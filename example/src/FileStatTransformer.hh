<?hh // strict

namespace hhpack\package\examples\classes;

use hhpack\package\SourceFile;
use hhpack\package\Stream;
use hhpack\package\ResourceStream;
use hhpack\package\Middleware;
use SplFileInfo;

final class FileStatTransformer implements Middleware<SourceFile, ResourceStream<SplFileInfo>>
{

    public function receive(Stream<SourceFile> $stream) : ResourceStream<SplFileInfo>
    {
        $factory = () ==> {
            foreach ($stream->items() as $source) {
                yield new SplFileInfo($source->name());
            }
        };

        return ResourceStream::fromItems( $factory() );
    }

}
