namespace HHPack\Package\Test;

use HHPack\Package\{Selector, ClassObject, SourceFile, ResourceStream};
use HHPack\Package\Test\Fixtures\Base;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class ResourceStreamTest extends HackTest {
  public function testStreamConsume(): void {
    $sourceStream = () ==> {
      yield new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    };
    $stream = new ResourceStream($sourceStream());

    $files = $stream->toImmVector();
    expect($files->count())->toBeSame(1);
  }

  public function testConcatStreams(): void {
    $sourceStream1 = () ==> {
      yield new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    };
    $stream1 = new ResourceStream($sourceStream1());

    $sourceStream2 = () ==> {
      yield new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    };

    $results =
      $stream1->concat(new ResourceStream($sourceStream2()))->toImmVector();
    expect($results->count())->toBeSame(2);
  }
}
