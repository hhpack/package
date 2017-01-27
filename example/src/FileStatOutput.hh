<?hh // strict

namespace HHPack\Package\Examples\Classes;

use HHPack\Package\Middleware;
use HHPack\Package\Stream;
use SplFileInfo;

final class FileStatOutput implements Middleware<SplFileInfo, void>
{

    public function receive(Stream<SplFileInfo> $stream) : void
    {
        foreach ($stream->items() as $stat) {
            echo $stat->getPathname(), ' - ', $stat->getSize(), 'bytes', PHP_EOL;
        }
    }

}
