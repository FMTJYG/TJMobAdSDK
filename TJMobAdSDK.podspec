

Pod::Spec.new do |spec|
  spec.name         = "TJMobAdSDK"
  spec.version      = "1.0.0"
  spec.summary      = "A description of the advertisement"
  
  spec.description  = <<-DESC
  A specific description of the advertisement.
                   DESC

  spec.homepage     = "https://github.com/FMTJYG/TJMobAdSDK"
  
  spec.license      = { :type => "MIT", :file => "LICENSE" }

  spec.author       = { "YG" => "yangguang@qingting.fm" }
  
  spec.platform     = :ios, "12.0"

  spec.source       = { :git => "https://github.com/FMTJYG/TJMobAdSDK.git", :tag => "#{spec.version}" }
  
  spec.vendored_frameworks = 'TJMobAdSDK.framework'
  
  spec.frameworks   = 'UIKit', 'Foundation', 'AVFoundation'
  
  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  
end
