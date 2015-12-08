<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\ClassObject;
use hhpack\package\SourceFile;
use hhpack\package\ClassStreamWrapper;
use hhpack\package\selector;
use hhpack\package\spec\fixtures\Base;

describe(ClassStreamWrapper::class, function () {
  beforeEach(function () {
    $stream = () ==> {
      yield new ClassObject(
        new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh')),
        'hhpack\\package\\spec\\fixtures',
        realpath(__DIR__ . '/fixtures')
      );
    };
    $this->wrapper = new ClassStreamWrapper($stream());
  });
  describe('select()', function () {
    context('when unmatched', function () {
      it('class file does not return', function () {
        $files = $this->wrapper->select(selector\implementsInterface('foo'))->toImmVector();
        expect($files->count())->toBe(0);
      });
    });
  });
});
