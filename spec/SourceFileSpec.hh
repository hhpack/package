<?hh //partial

namespace package\spec;

use package\SourceFile;
use package\spec\fixtures\Example1;

describe(SourceFile::class, function () {
  beforeEach(function () {
    $this->sourceFile = new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'));
  });
  describe('startsWith()', function () {
    context('when matched', function () {
      it('returns true', function () {
        $result = $this->sourceFile->startsWith(__DIR__);
        expect($result)->toBeTrue();
      });
    });
    context('when unmatched', function () {
      it('returns false', function () {
        $result = $this->sourceFile->startsWith('/Foo');
        expect($result)->toBeFalse();
      });
    });
  });
  describe('endsWith()', function () {
    context('when matched', function () {
      it('returns true', function () {
        $result = $this->sourceFile->endsWith('/Example1.hh');
        expect($result)->toBeTrue();
      });
    });
    context('when unmatched', function () {
      it('returns false', function () {
        $result = $this->sourceFile->endsWith(__DIR__);
        expect($result)->toBeFalse();
      });
    });
  });
});
