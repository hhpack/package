<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\SourceFile;
use HHPack\Package\Test\Fixtures\Example1;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class SourceFileTest extends HackTest {
  public function testStartsWithWhenMatched(): void {
    $sourceFile = new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    expect($sourceFile->startsWith(__DIR__))->toBeTrue();
  }

  public function testStartsWithWhenUnmatched(): void {
    $sourceFile = new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    expect($sourceFile->startsWith('/Foo'))->toBeFalse();
  }

  public function testEndsWithWhenMatched(): void {
    $sourceFile = new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    expect($sourceFile->endsWith('/Example1.hh'))->toBeTrue();
  }

  public function testEndsWithWhenUnmatched(): void {
    $sourceFile = new SourceFile(\realpath(__DIR__.'/fixtures/Example1.hh'));
    expect($sourceFile->endsWith(__DIR__))->toBeFalse();
  }
}
