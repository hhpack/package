<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\selector;
use hhpack\package\ClassObject;
use hhpack\package\SourceFile;
use hhpack\package\StreamObject;
use hhpack\package\spec\fixtures\Base;

describe(StreamObject::class, function () {
  beforeEach(function () {
    $stream = () ==> {
      yield new ClassObject(
        new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh')),
        'hhpack\\package\\spec\\fixtures',
        realpath(__DIR__ . '/fixtures')
      );
    };
    $this->wrapper = new StreamObject($stream());
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
