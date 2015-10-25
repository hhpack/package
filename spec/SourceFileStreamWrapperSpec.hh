<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\SourceFile;
use hhpack\package\SourceFileStreamWrapper;

describe(SourceFileStreamWrapper::class, function () {
  beforeEach(function () {
    $stream = () ==> {
      yield new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'));
    };
    $this->wrapper = new SourceFileStreamWrapper($stream());
  });
  describe('startsWith()', function () {
    context('when matched', function () {
      it('returns matched source files', function () {
        $files = $this->wrapper->startsWith(__DIR__)->toImmVector();
        expect($files->count())->toBe(1);
      });
    });
  });
  describe('endsWith()', function () {
    context('when matched', function () {
      it('returns matched source files', function () {
        $files = $this->wrapper->endsWith('1.hh')->toImmVector();
        expect($files->count())->toBe(1);
      });
    });
  });
});
