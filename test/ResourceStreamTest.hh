<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\{Selector, ClassObject, SourceFile, ResourceStream};
use HHPack\Package\Test\Fixtures\Base;
use HackPack\HackUnit\Contract\Assert;

final class ResourceStreamTest {
  <<Test>>
  public function streamConsume(Assert $assert): void {
    $sourceStream = () ==> {
      yield new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    };
    $stream = new ResourceStream($sourceStream());

    $files = $stream->toImmVector();
    $assert->int($files->count())->eq(1);
  }

  <<Test>>
  public function concatStreams(Assert $assert): void {
    $sourceStream1 = () ==> {
      yield new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    };
    $stream1 = new ResourceStream($sourceStream1());

    $sourceStream2 = () ==> {
      yield new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    };

    $results =
      $stream1->concat(new ResourceStream($sourceStream2()))->toImmVector();
    $assert->int($results->count())->eq(2);
  }
}
