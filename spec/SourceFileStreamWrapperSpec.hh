<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\SourceFile;
use hhpack\package\SourceFileStreamWrapper;
use hhpack\package\selector;

describe(SourceFileStreamWrapper::class, function () {
  beforeEach(function () {
    $stream = () ==> {
      yield new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'));
    };
    $this->wrapper = new SourceFileStreamWrapper($stream());
  });
  describe('select()', function () {
    context('when matched', function () {
      it('returns matched source files', function () {
        $files = $this->wrapper->select(selector\startsWith(__DIR__))->toImmVector();
        expect($files->count())->toBe(1);
      });
    });
  });
});
