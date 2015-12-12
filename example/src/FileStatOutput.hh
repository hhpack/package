<?hh // strict

namespace hhpack\package\examples\classes;

use hhpack\package\Middleware;
use hhpack\package\StreamWrapper;
use SplFileInfo;

final class FileStatOutput implements Middleware<SplFileInfo, void>
{

    public function receive(StreamWrapper<SplFileInfo> $stream) : void
    {
        foreach ($stream->items() as $stat) {
            echo $stat->getPath(), ' - ', $stat->getSize(), 'bytes', PHP_EOL;
        }
    }

}
