<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\selector;
use hhpack\package\ClassObject;
use hhpack\package\SourceFile;
use hhpack\package\ResourceStream;
use hhpack\package\spec\fixtures\Base;

describe(ResourceStream::class, function () {
  beforeEach(function () {
    $stream = () ==> {
      yield new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'));
    };
    $this->stream = new ResourceStream($stream());
  });
  describe('filter()', function () {
    context('when not matcher specified', function () {
      it('returns class files', function () {
        $files = $this->stream->toImmVector();
        expect($files->count())->toBe(1);
      });
    });
  });
  describe('concat()', function () {
    it('returns concat stream', function () {
      $stream = () ==> {
        yield new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'));
      };
      $results = $this->stream->concat(new ResourceStream($stream()))->toImmVector();
      expect($results->count())->toBe(2);
    });
  });
});
