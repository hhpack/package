namespace HHPack\Package\Examples\Classes;

use HHPack\Package\{SourceFile, Stream, ResourceStream, Middleware};
use SplFileInfo;

final class FileStatTransformer
  implements Middleware<SourceFile, ResourceStream<SplFileInfo>> {

  public function receive(
    Stream<SourceFile> $stream,
  ): ResourceStream<SplFileInfo> {
    $factory = () ==> {
      foreach ($stream->items() as $source) {
        yield new SplFileInfo($source->name());
      }
    };

    return ResourceStream::fromItems($factory());
  }

}
